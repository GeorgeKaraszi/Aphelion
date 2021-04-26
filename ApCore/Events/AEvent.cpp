#include "AEvent.hpp"
#include <ApInclude/fast_atio.hpp>
#include <ApCore/Core/TeamManager.hpp>

#define AP_ASSET_TM(manager) { AP_ASSERT(PRESENT_PTR(manager), "ApCore::Core::TeamManager is not initialized!") }

namespace ApCore::Events
{
  AEvent::AEvent(Core::TeamManager *manager)
  : m_team_manager(manager),
    m_websocket(Core::Network::GetNetwork()->GetWebSocket()),
    m_db(ApData::Sql::Database::GetDatabase()->Get())
  {
    m_tracking_id = m_websocket->DataEvent += [&](const JSON& data) {
      ProcessEvents(data);
    };
  }

  AEvent::~AEvent()
  {
    if(PRESENT_PTR(m_websocket))
    {
      StopTrackingEvents();
      m_websocket->DataEvent.RemoveListener(m_tracking_id);
    }
  }

  void AEvent::LoadRules()
  {
    _load_rules_impl();
  }

  bool AEvent::ProcessEvents(const JSON &data)
  {
    if(data.contains("payload"))
    {
      JSON payload = data["payload"];
      if(!payload.is_null() && payload.contains("event_name") && !payload["event_name"].is_null())
      {
        switch(event_type(payload))
        {
          case Event::BASE_CAPTURE:
            return _base_capture_event_impl(payload);
          case Event::DEATH:
            return _death_event_impl(payload);
          case Event::KILL:
            return _kill_event_impl(payload);
          case Event::HEAL_TICK:
            return _heal_tick_event_impl(payload);
          case Event::REVIVE_TICK:
            return _revive_tick_event_impl(payload);
          case Event::UNKNOWN:
          default:
            return false;
        }
      }
    }
      return false;
  }

  void AEvent::StartTrackingEvents()
  {
    auto request = generate_message("subscribe");
    m_websocket->DoWrite(request);
  }

  void AEvent::StopTrackingEvents()
  {
    auto request = generate_message("clearSubscribe");
    m_websocket->DoWrite(request);
  }

  AEvent::Event AEvent::event_type(const JSON &payload)
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
    int  exp_id   = fast_atoi(exp_id_s);

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

  std::string AEvent::generate_message(const std::string &action)
  {
    AP_ASSET_TM(m_team_manager)
    JSON subscribe_message;
    subscribe_message["service"]    = "event";
    subscribe_message["action"]     = action;
    subscribe_message["eventNames"] = _trackable_event_names_impl();

    if(!action.starts_with("clear"))
    {
      subscribe_message["characters"] = m_team_manager->player_ids();
    }

    return subscribe_message.dump(-1, ' ', true, JSON::error_handler_t::ignore);
  }
}