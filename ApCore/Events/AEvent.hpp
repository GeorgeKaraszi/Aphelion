#ifndef APCORE_EVENTS_AEVENT_HPP
#define APCORE_EVENTS_AEVENT_HPP

#include <ApCore/Core/Network.hpp>
#include <ApData/Sql/Database.hpp>

#define KILL_TRACK "GainExperience_experience_id_1"
#define HEAL_TICK_TRACK "GainExperience_experience_id_4"
#define HEAL_ASSIST_TRACK "GainExperience_experience_id_5"
#define REVIVE_TRACK "GainExperience_experience_id_7"
#define DEATH_TRACK "Death"
#define FACILITY_CONTROL_TRACK "FacilityControl"

namespace ApCore::Core
{
  class TeamManager;
}

namespace ApCore::Events
{
  class AEvent
  {
  public:
    enum Event { UNKNOWN, HEAL_TICK, REVIVE_TICK, KILL, DEATH, BASE_CAPTURE };

  public:
    AEvent()              = delete;
    AEvent(const AEvent&) = default;
    explicit AEvent(Core::TeamManager *manager);
    virtual ~AEvent();

  public:
    void LoadRules();
    bool ProcessEvents(const JSON& data);
    void StartTrackingEvents();
    void StopTrackingEvents();
    virtual void Reset() {};

  protected:
    virtual void _load_rules_impl()                                = 0;
    virtual std::vector<std::string> _trackable_event_names_impl() = 0;
    virtual bool _death_event_impl(const JSON& payload)        { return false; }
    virtual bool _kill_event_impl(const JSON& payload)         { return false; }
    virtual bool _base_capture_event_impl(const JSON& payload) { return false; }
    virtual bool _heal_tick_event_impl(const JSON& payload)    { return false; }
    virtual bool _revive_tick_event_impl(const JSON& payload)  { return false; }

  protected:
    static Event event_type(const JSON& payload);

  private:
    std::string generate_message(const std::string& action);

  protected:
    std::reference_wrapper<ApData::Sql::Database> m_db;
    Core::TeamManager *m_team_manager;
  private:
    std::shared_ptr<Nets::WebSocket> m_websocket;
    u_long m_tracking_id;
  };
}

#endif //APCORE_EVENTS_AEVENT_HPP
