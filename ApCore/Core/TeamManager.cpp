#include "TeamManager.hpp"
//#include <ApCore/Events/Outfit/OutfitEvent.hpp>
#include <ApCore/Events/POG/PogEvent.hpp>

# define AP_ASSERT_IDX(idx, teams) AP_ASSERT(((idx) >= 0 && (idx) < (teams).size()), "Team index is out of range!");

namespace ApCore::Core
{
  TeamManager::TeamManager(int size)
  : Teams(size), m_event(std::make_shared<Events::POG::PogEvent>(this))
  {
    m_event->LoadRules();
  }

  int TeamManager::SetSize(int size)
  {
    int size_diff = size - (int)Teams.size();

    m_event->StopTrackingEvents();

    if(size_diff < 0)
    {
      auto it = Teams.rbegin();
      for(int i = 0; i < size_diff || it != Teams.rend(); ++i, ++it)
      {
        RemoveTeam(*it);
      }
    }

    Teams.resize(size);
    return size_diff;
  }

  void TeamManager::RegisterTeam(int idx, const std::string& tag)
  {
    AP_ASSERT_IDX(idx, Teams)


    if(BLANK_PTR(Teams[idx]) || Teams[idx]->Tag != tag)
    {
      RemoveTeam(Teams[idx]);
      Teams[idx] = std::make_shared<Planetside::Team>(tag);
      Teams[idx]->GatherCensusInfo();
    }
  }

  void TeamManager::StartTrackingTeams()
  {
    m_event->StopTrackingEvents();
    m_event->StartTrackingEvents();
  }

  void TeamManager::RemoveTeam(TEAM_PTR team)
  {
    if(PRESENT_PTR(team))
    {
      team->Reset();
      team.reset();
    }
  }

  TeamManager::TEAM_PTR TeamManager::FindTeam(const std::string &outfit_id)
  {
    for(auto &team : Teams)
    {
      if(team->uuid == outfit_id)
      {
        return team;
      }
    }

    return nullptr;
  }

  Planetside::Team::PLAYER_PTR TeamManager::FindPlayer(const std::string &player_id)
  {
    for(auto &team : Teams)
    {
      if(team->ContainsPlayer(player_id))
      {
        return team->GetPlayer(player_id);
      }
    }

    return nullptr;
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