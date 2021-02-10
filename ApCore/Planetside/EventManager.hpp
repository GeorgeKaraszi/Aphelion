#ifndef APCORE_PLANETSIDE_EVENTMANAGER_HPP
#define APCORE_PLANETSIDE_EVENTMANAGER_HPP

#include <ApCore/Core/Network.hpp>

namespace ApCore::Core
{
  class TeamManager;
}

namespace ApCore::Planetside
{
  class EventManager
  {
  public:
    enum Event { UNKNOWN, HEAL_TICK, REVIVE_TICK, KILL, DEATH, BASE_CAPTURE };

  public:
    EventManager()                    = delete;
    EventManager(const EventManager&) = default;
    explicit EventManager(Core::TeamManager* manager);
    ~EventManager();
    void StartTrackingEvents();
    void StopTrackingEvents();

  private:
    void ProcessWebsocketData(const JSON& data);
    void update_players(const JSON& payload);
    void update_outfit(const JSON& payload);
    static Event event_type(const JSON& payload);
    std::string generate_message(const std::string& action);

  private:
    Core::TeamManager                   *m_team_manager;
    std::shared_ptr<Nets::WebSocket>    m_websocket;
    u_long                              tracking_id;
  };
}

#endif //APCORE_PLANETSIDE_EVENTMANAGER_HPP
