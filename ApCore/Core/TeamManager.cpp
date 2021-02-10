#include "TeamManager.hpp"

# define AP_ASSERT_IDX(idx, teams) AP_ASSERT(((idx) >= 0 && (idx) < (teams).size()), "Team index is out of range!");

namespace ApCore::Core
{
  TeamManager::TeamManager(int size) : Teams(size), m_event_manager(this)
  {}

  void TeamManager::SetSize(int size)
  {
    int size_diff = size - (int)Teams.size();

    m_event_manager.StopTrackingEvents();

    if(size_diff < 0)
    {
      auto it = Teams.rbegin();
      for(int i = 0; i < size_diff || it != Teams.rend(); ++i, ++it)
      {
        RemoveTeam(*it);
      }
    }

    Teams.resize(size);
  }

  void TeamManager::RegisterTeam(int idx, const std::string& tag)
  {
    AP_ASSERT_IDX(idx, Teams)

    m_event_manager.StopTrackingEvents();

    if(BLANK_PTR(Teams[idx]) || Teams[idx]->Tag != tag)
    {
      RemoveTeam(Teams[idx]);
      Teams[idx] = std::make_shared<Planetside::Team>(tag);
      Teams[idx]->GatherCensusInfo();
    }

    m_event_manager.StartTrackingEvents();
  }

  void TeamManager::RemoveTeam(TEAM_PTR team)
  {
    if(PRESENT_PTR(team))
    {
      team->Reset();
      team.reset();
    }
  }

  std::vector<std::string_view> TeamManager::player_ids()
  {
    std::vector<std::string_view> ids;
    for(const auto& team : Teams)
    {
      if(BLANK_PTR(team)) continue;
      auto player_ids = team->PlayerIds();
      ids.insert(ids.end(), player_ids.begin(), player_ids.end());
    }

    return ids;
  }

}