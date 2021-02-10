#ifndef APCORE_PLANETSIDE_PLAYER_HPP
#define APCORE_PLANETSIDE_PLAYER_HPP

#include <ApInclude/boost.hpp>
#include "AFaction.hpp"

namespace ApCore::Planetside
{
  class Player : public AFaction
  {
  public:
    enum LOADOUT_ { LOADOUT_HA, LOADOUT_LA, LOADOUT_ENGI, LOADOUT_INFIL, LOADOUT_MEDIC, LOADOUT_MAX, LOADOUT_UNK };
    typedef int LoadoutT;

  public:
    Player()              = default;
    Player(const Player&) = default;
    explicit Player(const JSON &player);

    void AddKill();
    void AddDeath();
    void AddScore(int points);
    void ToggleBenched();
    [[nodiscard]] bool KDPositive() const;
    [[nodiscard]] double KillDeathAverage() const;

    ApUI::Types::Color ScoreColor();
    ApUI::Types::Color KDColor();
  private:
    static LoadoutT Loadout(char profile_type);

  public:
    std::string uuid;
    std::string player_name;
    std::string alias_name;
    LoadoutT loadout{};
    long score       = 0;
    long kill_count  = 0;
    long death_count = 0;
    bool benched     = false;

  };
}

#endif //APCORE_PLANETSIDE_PLAYER_HPP
