#include "Team.hpp"
#include <fmt/format.h>
#include <ApCore/Core/Network.hpp>
#include <utility>
#include <iostream>

namespace ApCore::Planetside
{
  Team::Team(std::string tag) : Tag(std::move(tag))
  {}

  Team::Team(const JSON &team_roster, std::string tag) : Tag(std::move(tag))
  {
    InitializeRoster(team_roster);
  }

  Team::~Team()
  {
//    StopTracking();
  }

  void Team::GatherCensusInfo()
  {
    auto census = Core::Network::GetNetwork()->GetCensusAPI();
    InitializeRoster(census->GetOutfitRoster(Tag).data);
  }

  bool Team::InitializeRoster(const JSON &team_roster)
  {
    Reset();

    if(!team_roster.contains("outfit_list") ||
       !team_roster["outfit_list"].is_array() ||
       !team_roster["outfit_list"].front().contains("members")
       )
    {
      return false;
    }

    auto outfit = team_roster["outfit_list"].front();
    SetFaction(outfit["outfits_faction"]["faction_id"].get<std::string>()[0]);
    outfit["alias_lower"].get_to(Tag);
    outfit["name"].get_to(Name);
    outfit["outfit_id"].get_to(uuid);

    TagName     = fmt::format("[{}] {}", Tag, Name);
    LoadingTeam = true;

    for(auto &player : outfit["members"])
    {
      if(player["character"]["status"]["online_status"] != "0")
      {
        AddPlayer(player["character"]);
      }
    }

    LoadingTeam = false;

//    StartTracking();
    return true;
  }

  bool Team::DigestPlayerInfo(const JSON &player_info)
  {
    return true;
  }

  Team::PLAYER_PTR Team::AddPlayer(const JSON &player_data)
  {
    auto id = player_data["character_id"].get<std::string>();

    if(!ContainsPlayer(id))
    {
      m_player_map[id] = Players.emplace_back(std::make_shared<Player>(this, player_data));
    }

    return m_player_map[id];
  }

  Team::PLAYER_PTR Team::operator[](const std::string &id)
  {
    return GetPlayer(id);
  }

  Team::PLAYER_PTR Team::GetPlayer(const std::string &id)
  {
    return m_player_map[id];
  }

  std::vector<std::string_view> Team::PlayerIds()
  {
    std::vector<std::string_view> ids;

    for(const auto &x : Players)
    {
      ids.push_back(x->uuid);
    }

    return ids;
  }

  void Team::AddTeamScore(int points)
  {
    Score += points;
  }

  long Team::GetScore()
  {
    long total_score = Score;
    if(!LoadingTeam)
    {
      for (auto const& player : Players)
      {
        total_score += player->score;
      }
    }

    return total_score;
  }

  [[maybe_unused]] void Team::AddScore(const std::string& player_id, int points)
  {
    if(ContainsPlayer(player_id))
    {
      Score += points;
      m_player_map[player_id]->AddScore(points);
    }
  }

  [[maybe_unused]] void Team::ActivePlayers(const std::function<void(Team::PLAYER_PTR)>& callback)
  {
    for(const auto &x : Players)
    {
      if(!x->benched)
        callback(x);
    }
  }

  bool Team::ContainsPlayer(const std::string &id)
  {
    return PRESENT_PTR(m_player_map[id]);
  }

  void Team::StartTracking()
  {
//    if(tracking_id)
//      StopTracking();

    auto websocket = Core::Network::GetNetwork()->GetWebSocket();
    tracking_id    = websocket->DataEvent += [&](const JSON &websocket_data){
      DigestPlayerInfo(websocket_data);
    };

//    "service":"event",
//        "action":"subscribe",
//        "characters":["5428010618015189713"],
//    "eventNames":["Death"]
    JSON request;
    request["service"]    = "event";
    request["action"]     = "subscribe";
    request["characters"] = PlayerIds();
    request["eventNames"] = {"Death", "GainExperience"};

    websocket->DoWrite(request.dump());
  }

  void Team::StopTracking()
  {
    if(tracking_id == 0) return;
    auto websocket = Core::Network::GetNetwork()->GetWebSocket();
    websocket->DataEvent.RemoveListener(tracking_id);

    JSON request;
    request["service"]    = "event";
    request["action"]     = "clearSubscribe";
    request["characters"] = PlayerIds();
    request["eventNames"] = {"Death", "GainExperience"};

    websocket->DoWrite(request.dump());

    tracking_id = 0;
  }

  void Team::Reset()
  {
    m_player_map.clear();
    Players.clear();
    Score = 0;
  }
}