#include "ScoreContent.hpp"
#include <ApUI/Widgets/Buttons/ButtonColored.hpp>

namespace ApGame::Contents
{

  ScoreContent::ScoreContent()
  {
    using namespace ApUI::Types;
    using namespace ApUI::Widgets;
    using namespace ApUI::Plugins;


    TeamDataTemplate team_1 = {
        .name         = "Test",
        .tag          = "TST",
        .empire_color = Color::Faction_TR,
        .players      = { "Big", "And", "Dumb", "Frog" }
    };

    TeamDataTemplate team_2 = {
        .name         = "Other Test",
        .tag          = "TST2",
        .empire_color = Color::Faction_VS,
        .players      = { "Player 1", "Player 2", "Player 3" }
    };

    m_teams.push_back(team_1);
    m_teams.push_back(team_2);


    m_team_header = &CreateWidget<Columns::Column>();
    m_team_score  = &CreateWidget<Columns::Column>();

    for(const auto &team : m_teams)
    {
      std::string header = "[" + team.tag + "] " + team.name;
      m_team_header->CreateWidget<Buttons::ButtonColored>(header.c_str(), ImVec2(-FLT_MIN, 30.0f), team.empire_color);
      auto *body = &m_team_score->CreateWidget<Layout::Group>();
      for(const auto &player : team.players)
      {
        auto btn = &body->CreateWidget<Buttons::ButtonColored>(player.c_str(), ImVec2(-FLT_MIN, 30.0f), team.empire_color);
        btn->SetFlags(ImGuiButtonFlags_AlignTextBaseLine);
      }
    }
  }
}