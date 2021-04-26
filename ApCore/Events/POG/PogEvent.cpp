#include "PogEvent.hpp"
#include <ApInclude/fast_atio.hpp>
#include <ApCore/Core/TeamManager.hpp>
#include <ApData/Sql/Models/Event.hpp>
#include <ApData/Sql/Models/Item.hpp>
#include <ApData/Sql/Models/Loadout.hpp>
#include <fmt/color.h>

namespace ApCore::Events::POG
{
  void PogEvent::Reset()
  {
    m_current_team = nullptr;
  }

  void PogEvent::_load_rules_impl()
  {
    m_rules = ApData::Sql::Query::PogQuery::GetPogRules(m_db);
  }

  std::vector<std::string> PogEvent::_trackable_event_names_impl()
  {
    return { DEATH_TRACK, FACILITY_CONTROL_TRACK };
  }

  // {
  //        "attacker_character_id": "5428010618015189713",
  //        "attacker_fire_mode_id": "26103",
  //        "attacker_loadout_id": "15",
  //        "attacker_vehicle_id": "0",
  //        "attacker_weapon_id": "26003",
  //        "character_id": "5428168624838258657",
  //        "character_loadout_id": "6",
  //        "event_name": "Death",
  //        "is_headshot": "1",
  //        "timestamp": "1392056954",
  //        "vehicle_id": "0",
  //        "world_id": "1",
  //        "zone_id": "2"
  //    }

  bool PogEvent::_death_event_impl(const JSON &payload)
  {
    using namespace ApCore::Planetside;

    auto attacker_id          = payload["attacker_character_id"].get<std::string>();
    auto attacker_loadout_id  = fast_atoi(payload["attacker_loadout_id"].get<std::string>());
    auto attacker_weapon_id   = fast_atoi(payload["attacker_weapon_id"].get<std::string>());
    auto defender_id          = payload["character_id"].get<std::string>();
    auto defender_loadout_id  = fast_atoi(payload["character_loadout_id"].get<std::string>());
    bool headshot             = payload["is_headshot"].get<std::string>()[0] == '1';
    bool attacker_is_max      = AP_VEC_MATCH_FOUND(m_rules.banned_profile_ids, attacker_loadout_id);
    bool defender_is_max      = AP_VEC_MATCH_FOUND(m_rules.banned_profile_ids, defender_loadout_id);
    bool team_kill            = false;
    bool suicide              = false;
    Team::PLAYER_PTR attacker = nullptr;
    Team::PLAYER_PTR defender = nullptr;

    for(const auto &team : *m_team_manager)
    {
      if(BLANK_PTR(team)) continue;
      bool contains_attacker = team->ContainsPlayer(attacker_id);
      bool contains_defender = team->ContainsPlayer(defender_id);

      if(BLANK_PTR(attacker) && contains_attacker)
      {
        attacker = team->GetPlayer(attacker_id);
      }

      if(BLANK_PTR(defender) && contains_defender)
      {
        defender = team->GetPlayer(defender_id);
      }

      if(contains_attacker && contains_defender)
      {
        team_kill = attacker != defender;
        suicide   = !team_kill;
      }
    }

    if(BLANK_PTR(attacker) || BLANK_PTR(defender) || attacker->benched || defender->benched)
    {
      return false;
    }

    if(AP_VEC_MATCH_FOUND(m_rules.banned_item_ids, attacker_weapon_id))
    {
      return true;
    }

    defender->AddDeath();

    if(team_kill)
    {
      attacker->AddScore(attacker_is_max ? m_rules.max_team_kill : m_rules.team_kill);
    }
    else if(suicide)
    {
      attacker->AddScore(attacker_is_max ? m_rules.max_suicide : m_rules.suicide);
    }
    else
    {
      attacker->AddKill(headshot);
      attacker->AddScore(defender_is_max ? m_rules.max_kill : m_rules.kill);
      defender->AddScore(m_rules.death);
    }

    auto item_db    = ApData::Sql::Models::Item(m_db);
    auto loadout_db = ApData::Sql::Models::Loadout(m_db);
    auto weapon     = item_db.FindByItemID(attacker_weapon_id);
    auto loadout    = loadout_db.FetchByProfileID(attacker_loadout_id);

    fmt::print(
        fmt::emphasis::bold | fg(fmt::color::red),
        "[{}] {} killed [{}] {} | with: [{}]{} As: {}\n",
        attacker->team->Tag,
        attacker->player_name,
        defender->team->Tag,
        defender->player_name,
        weapon.id,
        weapon.name,
        loadout.empty() ? "Unknown" : loadout.front().name
    );
    return true;
  }

  // {"payload":{
  // "duration_held":"2451",
  // "event_name":"FacilityControl",
  // "facility_id":"210001",
  // "new_faction_id":"2",
  // "old_faction_id":"2",
  // "outfit_id":"37577209674238761",
  // "timestamp":"1613248090",
  // "world_id":"13",
  // "zone_id":"6"
  // },
  // "service":"event",
  // "type":"serviceMessage"}
  bool PogEvent::_base_capture_event_impl(const JSON &payload)
  {
    if(!payload.contains("outfit_id"))
      return false;

    auto outfit_id = payload["outfit_id"].get<std::string>();
    auto team      = m_team_manager->FindTeam(outfit_id);

    if(BLANK_PTR(team))
    {
      return false;
    }

    else if(BLANK_PTR(m_current_team))
    {
      team->AddTeamScore(m_rules.base_capture);   // Base was captured for the first time in the round
    }
    else if(m_current_team->uuid != outfit_id)
    {
      team->AddTeamScore(m_rules.base_recapture); // Base was recaptured by the other team
    }

    m_current_team = team.get();
    return true;
  }

}