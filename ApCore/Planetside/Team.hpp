#ifndef APCORE_PLANETSIDE_TEAM_HPP
#define APCORE_PLANETSIDE_TEAM_HPP

#include <ApInclude/macros.h>
#include "AFaction.hpp"
#include "Player.hpp"

namespace ApCore::Planetside
{
  class Team : public AFaction
  {
  public:
    using PLAYER_PTR  = std::shared_ptr<Player>;

  public:
    Team()            = default;
    Team(const Team&) = default;
    ~Team();
    explicit Team(std::string tag);
    explicit Team(const JSON &team_roster, std::string tag = "");

    void GatherCensusInfo();
    bool InitializeRoster(const JSON &team_roster);
    bool DigestPlayerInfo(const JSON &player_info);
    PLAYER_PTR AddPlayer(const JSON &player_data);
    PLAYER_PTR operator[](const std::string& id);
    PLAYER_PTR GetPlayer(const std::string& id);
    std::vector<std::string_view> PlayerIds();

    void AddTeamScore(int points);
    long GetScore();
    [[maybe_unused]] void AddScore(const std::string& player_id, int points);
    [[maybe_unused]] void ActivePlayers(const std::function<void(PLAYER_PTR)>& callback);
    bool ContainsPlayer(const std::string& id);

    void StartTracking();
    void StopTracking();

    void Reset();

    [[nodiscard]] size_t size() const noexcept             { return Players.size(); }
    std::vector<PLAYER_PTR>::iterator begin()              { return Players.begin(); }
    std::vector<PLAYER_PTR>::iterator end()                { return Players.end(); }
    [[maybe_unused]] [[nodiscard]]
    std::vector<PLAYER_PTR>::const_iterator cbegin() const { return Players.cbegin(); }
    [[nodiscard]]
    std::vector<PLAYER_PTR>::const_iterator cend()   const { return Players.cend(); }

  public:
    std::string Tag;
    std::string Name;
    std::string TagName;
    std::string uuid;
    std::vector<PLAYER_PTR> Players;
    long Score       { 0 };
    bool LoadingTeam { false };
  private:
    u_long tracking_id   { 0 };
    std::map<std::string, PLAYER_PTR> m_player_map;

  };
}

#endif //APCORE_PLANETSIDE_TEAM_HPP
