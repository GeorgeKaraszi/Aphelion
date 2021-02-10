#include "ScoreContent.hpp"
#include <ApInclude/string_helper.hpp>
#include <ApUI/Widgets/Layout/Dummy.hpp>
#include <ApUI/Widgets/Layout/Separator.hpp>
#include <ApUI/Widgets/Layout/NewLine.hpp>

using namespace ApCore;

namespace ApGame::Contents
{

  ScoreContent::ScoreContent() : TeamManager(2)
  {
    TeamManager.RegisterTeam(0, "fooi");
    TeamManager.RegisterTeam(1, "twc2");
  }

  void ScoreContent::_Draw_Impl()
  {
    using namespace ApUI;
    using namespace ApUI::Widgets;
    using namespace ApUI::Plugins;
    auto col_flags = ImGuiTableColumnFlags_WidthStretch;
    auto tbl_flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedSame;

    DrawWidgets();
    Layout::Dummy(ImVec2(-FLT_MIN, 25.0f)).Draw();

    for(size_t i = 0; i < TeamManager.size(); i++)
    {
      if(BLANK_PTR(TeamManager[i])) continue;

      auto team      = TeamManager[i];
      auto table     = Tables::Table(tbl_flags, col_flags);
      auto color     = team->EmpireColor();
      auto color_vec = color.ToImVec4();
      table.AddStyle(ImGuiCol_TableHeaderBg, color_vec);
      table.AddStyle(ImGuiCol_HeaderActive,  color_vec);
      table.AddStyle(ImGuiCol_HeaderHovered, color_vec);
      table.AddColumns({"Name", "Score", "Kills", "Deaths", "KD"});



      if(!team->LoadingTeam)
      {
        for (const auto &player : *team)
        {
          auto &row = table.CreateRow(player->uuid);
          row["Name"].SetValues(player->player_name, color);
          row["Score"].SetValues(std::to_string(player->score), player->ScoreColor());
          row["Kills"].SetValues(std::to_string(player->kill_count), color);
          row["Deaths"].SetValues(std::to_string(player->death_count), color);
          row["KD"].SetValues(to_string(player->KillDeathAverage(), "%.2f"), player->KDColor());
        }
      }

      Texts::TextColored(team->TagName, team->EmpireColor()).Draw();
      table.Draw();

      if((i+1) < TeamManager.size())
      {
        auto new_line = Layout::NewLine();
        new_line.Draw();
        Layout::Separator().Draw();
        new_line.Draw();
      }
    }
  }
}