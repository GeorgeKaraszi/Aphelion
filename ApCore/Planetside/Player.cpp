#include "Player.hpp"

namespace ApCore::Planetside
{
  Player::Player(Team* current_team, const JSON &player) : team(current_team)
  {
    SetFaction(player["faction_id"].get<std::string>()[0]);
    loadout = Loadout(player["profile"]["profile_type_description"].get<std::string>()[0]);
    player["character_id"].get_to(uuid);
    player["name"]["first"].get_to(player_name);
  }

  void Player::AddKill(bool is_headshot)
  {
    if(is_headshot)
    {
      headshot_count++;
    }

    kill_count++;
  }

  void Player::AddDeath()
  {
    death_count++;
  }

  void Player::RemoveDeath()
  {
    if(death_count > 0)
      death_count--;
  }

  void Player::AddHealTick()
  {
    heal_ticks++;
  }

  void Player::AddReviveTick()
  {
    revive_ticks++;
  }

  void Player::AddScore(int points)
  {
    score += points;
  }

  void Player::ToggleBenched()
  {
    benched = !benched;
  }

  bool Player::KDPositive() const
  {
    return KillDeathAverage() >= 1.0f;
  }

  double Player::KillDeathAverage() const
  {
    return death_count == 0 ? kill_count : (kill_count / death_count);
  }

  double Player::HSRAverage() const
  {
    return kill_count == 0 ? 0 : (headshot_count / kill_count) * 100;
  }

  ApUI::Types::Color Player::KDColor() const
  {
    if(kill_count == death_count)
    {
      return ApUI::Types::Color::Yellow;
    }

    return KDPositive() ? ApUI::Types::Color::Green : ApUI::Types::Color::Red;
  }

  ApUI::Types::Color Player::ScoreColor() const
  {
    if(score == 0)
    {
      return ApUI::Types::Color::Yellow;
    }
    else if(score > 0)
    {
      return ApUI::Types::Color::Green;
    }

    return ApUI::Types::Color::Red;
  }

  Player::LoadoutT Player::Loadout(char profile_type)
  {
    switch(profile_type)
    {
      case 'H': // Heavy Assault
        return LOADOUT_HA;
      case 'L': // Light Assault
        return LOADOUT_LA;
      case 'C': // Combat Medic
        return LOADOUT_MEDIC;
      case 'E': // Engineer
        return LOADOUT_ENGI;
      case 'I': // Infiltrator
        return LOADOUT_INFIL;
      case 'D': // Defector / Max
      case 'M': // Max
        return LOADOUT_MAX;
      default:
        return LOADOUT_UNK;
    }
  }
}