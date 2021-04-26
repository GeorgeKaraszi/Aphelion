#include "OutfitEvent.hpp"
#include <ApCore/Core/TeamManager.hpp>

namespace ApCore::Events::Outfit
{
  OutfitEvent::OutfitEvent(Core::TeamManager *manager)
  : ApCore::Events::AEvent(manager)
  {}

  std::vector<std::string> OutfitEvent::_trackable_event_names_impl()
  {
    return {
      HEAL_TICK_TRACK,
      HEAL_ASSIST_TRACK,
      REVIVE_TRACK,
      DEATH_TRACK
    };
  }

  bool OutfitEvent::_death_event_impl(const JSON &payload)
  {
    using namespace ApCore::Planetside;

    auto attacker_id  = payload["attacker_character_id"].get<std::string>();
    auto defender_id  = payload["character_id"].get<std::string>();
    bool headshot     = payload["is_headshot"].get<std::string>()[0] == '1';
    auto attacker     = m_team_manager->FindPlayer(attacker_id);
    auto defender     = m_team_manager->FindPlayer(defender_id);

    if(BLANK_PTR(attacker) && BLANK_PTR(defender))
    {
      return false;
    }

    if(PRESENT_PTR(attacker))
    {
      attacker->AddKill(headshot);
      attacker->AddScore(1);
    }

    if(PRESENT_PTR(defender))
    {
      defender->AddDeath();
      defender->AddScore(-1);
    }

    return true;
  }

/* ----- Heal & Revive Payload -----
{
    "payload": {
      "amount": "15",
      "character_id": "5428752043483866993",
      "event_name": "GainExperience",
      "experience_id": "4",
      "loadout_id": "11",
      "other_id": "8252885335327625297",
      "timestamp": "1572796307",
      "world_id": "13",
      "zone_id": "2"
    },
    "service": "event",
    "type": "serviceMessage"
  }
*/
  bool OutfitEvent::_revive_tick_event_impl(const JSON& payload)
  {
    auto medic_player_id   = payload["character_id"].get<std::string>();
    auto revived_player_id = payload["other_id"].get<std::string>();
    auto medic_player      = m_team_manager->FindPlayer(medic_player_id);
    auto revived_player    = m_team_manager->FindPlayer(revived_player_id);

    if(PRESENT_PTR(medic_player))
    {
      medic_player->AddReviveTick();
    }

    if(PRESENT_PTR(revived_player))
    {
      revived_player->RemoveDeath();
    }

   return true;
  }

  bool OutfitEvent::_heal_tick_event_impl(const JSON& payload)
  {
    auto player_id = payload["character_id"].get<std::string>();
    auto player    = m_team_manager->FindPlayer(player_id);

    if(PRESENT_PTR(player))
    {
      player->AddHealTick();
    }

    return true;
  }
}