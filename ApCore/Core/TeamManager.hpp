#ifndef APCORE_CORE_TEAMMANAGER_HPP
#define APCORE_CORE_TEAMMANAGER_HPP

#include "Network.hpp"
#include <ApCore/Planetside/EventManager.hpp>
#include <ApCore/Planetside/Team.hpp>

namespace ApCore::Core
{
  class TeamManager
  {
    using TEAM_PTR = std::shared_ptr<Planetside::Team>;
  public:
    enum Event { UNKNOWN, HEAL_TICK, REVIVE_TICK, KILL, BASE_CAPTURE };
  public:
    explicit TeamManager(int size = 1);

    void SetSize(int size);
    void RegisterTeam(int idx, const std::string &tag);
    static void RemoveTeam(TEAM_PTR team);

    [[nodiscard]]
    size_t size() const noexcept                         { return Teams.size(); }
    TEAM_PTR operator[](const size_t pos) noexcept       { return Teams[pos]; }
    std::vector<TEAM_PTR>::iterator begin()              { return Teams.begin(); }
    std::vector<TEAM_PTR>::iterator end()                { return Teams.end(); }
    [[nodiscard]]
    std::vector<TEAM_PTR>::const_iterator cbegin() const { return Teams.cbegin(); }
    [[nodiscard]]
    std::vector<TEAM_PTR>::const_iterator cend()   const { return Teams.cend(); }
  private:
    std::vector<std::string_view> player_ids();

  public:
    std::vector<TEAM_PTR> Teams;

  private:
    Planetside::EventManager m_event_manager;
    friend class ApCore::Planetside::EventManager;
  };
}

#endif //APCORE_CORE_TEAMMANAGER_HPP
