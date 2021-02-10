#include "EventManager.hpp"
#include <ApCore/Core/TeamManager.hpp>

#define AP_ASSET_TM(manager) { AP_ASSERT(PRESENT_PTR(manager), "ApCore::Core::TeamManager is not initialized!") }

namespace ApCore::Planetside
{
  EventManager::EventManager(Core::TeamManager *manager) :
  m_team_manager(manager), m_websocket(Core::Network::GetNetwork()->GetWebSocket())
  {
    tracking_id = m_websocket->DataEvent.AddListener([&](const JSON& data) { ProcessWebsocketData(data); });
  }

  EventManager::~EventManager()
  {
    m_websocket->DataEvent.RemoveListener(tracking_id);
  }

  void EventManager::StartTrackingEvents()
  {
    AP_ASSET_TM(m_team_manager)
    StopTrackingEvents();
    auto request = generate_message("subscribe");
    m_websocket->DoWrite(request);
  }

  void EventManager::StopTrackingEvents()
  {
    AP_ASSET_TM(m_team_manager)
    auto request = generate_message("clearSubscribe");
    m_websocket->DoWrite(request);
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

  /* ----- Death (AKA Kill) payload -----
    {
      "payload": {
        "attacker_character_id": "5428010618015189713",
        "attacker_fire_mode_id": "26103",
        "attacker_loadout_id": "15",
        "attacker_vehicle_id": "0",
        "attacker_weapon_id": "26003",
        "character_id": "5428168624838258657",
        "character_loadout_id": "6",
        "event_name": "Death",
        "is_headshot": "1",
        "timestamp": "1392056954",
        "vehicle_id": "0",
        "world_id": "1",
        "zone_id": "2"
      },
      "service": "event",
      "type": "serviceMessage"
    }
*/

  void EventManager::ProcessWebsocketData(const JSON &data)
  {
    if(!data.contains("payload"))
      return;

    JSON payload = data["payload"];
    if(payload.is_null() || !payload.contains("event_name") || payload["event_name"].is_null())
      return;

    auto event = event_type(payload);

    switch(event)
    {
      case Event::DEATH:
        update_players(payload);
      case Event::BASE_CAPTURE:
        update_outfit(payload);
      default:
        return;
    }
  }

  void EventManager::update_players(const JSON &payload)
  {
    auto attacker_id          = payload["attacker_character_id"].get<std::string>();
    auto attacker_loadout_id  = payload["attacker_loadout_id"].get<std::string>();
    auto defender_id          = payload["character_id"].get<std::string>();
    auto defender_load_id     = payload["character_loadout_id"].get<std::string>();
    bool headshot             = payload["is_headshot"].get<std::string>()[0] == '1';
    bool team_kill            = false;
    Team::PLAYER_PTR attacker = nullptr;
    Team::PLAYER_PTR defender = nullptr;

    for(const auto &team : *m_team_manager)
    {
      if(BLANK_PTR(team)) continue;
      bool contains_attacker = team->ContainsPlayer(attacker_id);
      bool contains_defender = team->ContainsPlayer(defender_id);
      if(BLANK_PTR(attacker) && contains_attacker) attacker = team->GetPlayer(attacker_id);
      if(BLANK_PTR(defender) && contains_defender) defender = team->GetPlayer(defender_id);

      team_kill = team->GetPlayer(attacker_id) && team->GetPlayer(defender_id);
    }
    if(team_kill)
    {
      attacker->AddScore(-5);
      defender->AddDeath();
    }
    else if(PRESENT_PTR(attacker))
    {
      attacker->AddKill();
      attacker->AddScore(1);
    }
    else if(PRESENT_PTR(defender))
    {
      defender->AddDeath();
      defender->AddScore(-1);
    }
    else if(PRESENT_PTR(attacker) && PRESENT_PTR(defender))
    {
      if(attacker->benched || defender->benched)
        return;

      attacker->AddKill();
      attacker->AddScore(1);
      defender->AddDeath();
      defender->AddScore(-1);
    }
  }

  void EventManager::update_outfit(const JSON &payload)
  {
    if(!payload.contains("outfit_id"))
      return;

    auto outfit_id = payload["outfit_id"].get<std::string>();
    auto team = std::find_if(m_team_manager->begin(), m_team_manager->end(), [outfit_id] (const auto &team) {
      return PRESENT_PTR(team) && team->uuid == outfit_id;
    });

    if(team != m_team_manager->end())
    {
      (*team)->Score += 10;
    }

  }

  EventManager::Event EventManager::event_type(const JSON &payload)
  {
    auto event_name = payload["event_name"].get<std::string>();
    if(event_name == "FacilityControl")
    {
      return Event::BASE_CAPTURE;
    }
    else if(event_name == "Death")
    {
      return Event::DEATH;
    }

    auto exp_id_s = payload["experience_id"].get<std::string>();
    int  exp_id   = exp_id_s.empty() ? -1 : std::stoi(exp_id_s);

    switch(exp_id)
    {
      case 1: // KILL_ID
        return Event::KILL;
      case 4: // HEAL_TICK_ID
      case 5: // HEAL_ASSIST_ID
        return Event::HEAL_TICK;
      case 7: // REVIVE_TICK_ID
        return Event::REVIVE_TICK;
      default:
        return Event::UNKNOWN;
    }
  }

  std::string EventManager::generate_message(const std::string &action)
  {
    JSON subscribe_message;
    subscribe_message["service"]    = "event";
    subscribe_message["action"]     = action;
    subscribe_message["characters"] = m_team_manager->player_ids();
    subscribe_message["eventNames"] = {
        "GainExperience_experience_id_1", // kill
        "GainExperience_experience_id_4", // Heal Player
        "GainExperience_experience_id_5", // Heal Assist
        "GainExperience_experience_id_7", // Revive
        "Death",                          // Kill / Death
        "FacilityControl"                 // Base capture / defended
    };

    return subscribe_message.dump(-1, ' ', true);
  }
}