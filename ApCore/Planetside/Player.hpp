#ifndef APCORE_PLANETSIDE_PLAYER_HPP
#define APCORE_PLANETSIDE_PLAYER_HPP

#include <ApInclude/boost.hpp>
#include "AFaction.hpp"

namespace ApCore::Planetside
{
  class Team;
  class Player : public AFaction
  {
  public:
    enum LOADOUT_ { LOADOUT_HA, LOADOUT_LA, LOADOUT_ENGI, LOADOUT_INFIL, LOADOUT_MEDIC, LOADOUT_MAX, LOADOUT_UNK };
    typedef int LoadoutT;

  public:
    Player()              = default;
    Player(const Player&) = default;
    explicit Player(Team* current_team, const JSON &player);

    void AddKill(bool is_headshot = false);
    void AddDeath();
    void RemoveDeath();
    void AddHealTick();
    void AddReviveTick();
    void AddScore(int points);
    void ToggleBenched();
    [[nodiscard]] bool KDPositive() const;
    [[nodiscard]] double KillDeathAverage() const;
    [[nodiscard]] double HSRAverage() const;
    [[nodiscard]] ApUI::Types::Color ScoreColor() const;
    [[nodiscard]] ApUI::Types::Color KDColor() const;
  private:
    static LoadoutT Loadout(char profile_type);

  public:
    std::string uuid;
    std::string player_name;
    std::string alias_name;
    LoadoutT loadout{};
    Team *team          = nullptr;
    long score          = 0;
    long kill_count     = 0;
    long death_count    = 0;
    long heal_ticks     = 0;
    long revive_ticks   = 0;
    long headshot_count = 0;
    bool benched        = false;

  };
}

#endif //APCORE_PLANETSIDE_PLAYER_HPP
