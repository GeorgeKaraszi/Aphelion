#ifndef APCORE_CORE_TEAMMANAGER_HPP
#define APCORE_CORE_TEAMMANAGER_HPP

#include "Network.hpp"
#include <ApCore/Events/AEvent.hpp>
#include <ApCore/Planetside/Team.hpp>

namespace ApCore::Core
{
  class TeamManager
  {
    using TEAM_PTR = std::shared_ptr<Planetside::Team>;
  public:
    explicit TeamManager(int size = 1);

    void SetSize(int size);
    void RegisterTeam(int idx, const std::string &tag);
    void StartTrackingTeams();
    static void RemoveTeam(TEAM_PTR team);

    TEAM_PTR FindTeam(const std::string &outfit_id);
    Planetside::Team::PLAYER_PTR FindPlayer(const std::string &player_id);
    std::vector<std::string_view> player_ids();

    [[nodiscard]]
    size_t size() const noexcept                         { return Teams.size(); }
    TEAM_PTR operator[](const size_t pos) noexcept       { return Teams[pos]; }
    std::vector<TEAM_PTR>::iterator begin()              { return Teams.begin(); }
    std::vector<TEAM_PTR>::iterator end()                { return Teams.end(); }
    [[maybe_unused]] [[nodiscard]]
    std::vector<TEAM_PTR>::const_iterator cbegin() const { return Teams.cbegin(); }
    [[nodiscard]]
    std::vector<TEAM_PTR>::const_iterator cend()   const { return Teams.cend(); }

  public:
    std::vector<TEAM_PTR> Teams;

  private:
    std::shared_ptr<Events::AEvent> m_event;
    friend class Events::AEvent;
  };
}

#endif //APCORE_CORE_TEAMMANAGER_HPP
