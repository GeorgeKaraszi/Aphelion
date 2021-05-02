#include "ScoreContent.hpp"
#include <fmt/format.h>
#include <ApUI/Widgets/Layout/Dummy.hpp>
#include <ApUI/Widgets/Layout/SameLine.hpp>
#include <ApUI/Widgets/Layout/Separator.hpp>
#include <ApUI/Widgets/Layout/NewLine.hpp>

using namespace ApCore;

namespace ApGame::Contents
{

  const auto tbl_options_g = ApUI::Widgets::Tables::TableOptions {
    .TableFlags = ImGuiTableFlags_NoSavedSettings |
                  ImGuiTableFlags_Resizable |
                  ImGuiTableFlags_RowBg
  };

  class TeamTable : public ApUI::Widgets::Layout::Group
  {
  public:
    explicit TeamTable(ApCore::Planetside::Team *team)
    : m_team(team),
      m_header(&CreateWidget<ApUI::Widgets::Layout::Group>()),
      m_table(&CreateWidget<ApUI::Widgets::Tables::Table>(team->Tag.c_str(), tbl_options_g))
    {
      AP_ASSERT(PRESENT_PTR(m_team), fmt::format("Widget id = {} : Team must be a valid Pointer!", widget_id));

      auto color     = team->EmpireColor();
      auto color_vec = color.ToImVec4();
      m_table->AddColumns({"Name", "Total Points", "Net Score", "Kills", "Deaths", "KD"});
      m_table->AddStyle(ImGuiCol_TableHeaderBg, color_vec);
      m_table->AddStyle(ImGuiCol_HeaderActive,  color_vec);
      m_table->AddStyle(ImGuiCol_HeaderHovered, color_vec);
    }

  protected:
    void _Draw_Impl() override
    {
      AP_ASSERT(PRESENT_PTR(m_team), fmt::format("Widget id = {} : Team must be a valid Pointer!", widget_id));
      if(!m_team_loaded && !m_team->LoadingTeam)
      {
        CreateHeaderWidgets();
        LoadPlayers();
        m_team_loaded = true;
      }

      DrawWidgets();
    }

  private:

    void CreateHeaderWidgets()
    {
      using namespace ApUI;
      using namespace ApUI::Widgets;

      auto color = m_team->EmpireColor();
      // OutfitName  [:Right Alignment Space:]  Score NN
      m_header->CreateWidget<Texts::TextColored>(m_team->TagName, color);

      m_header->CreateWidget<Layout::SameLine>()
              .AddPlugin<Plugins::DataDispatcher<ImVec2>>()
              .RegisterGatherer([&](){
                auto team_score = TeamScore();
                return ImVec2(ImGui::GetWindowWidth() - ImGui::CalcTextSize(team_score.c_str()).x - 1, 0);
              });

      m_header->CreateWidget<Texts::TextColored>("Score 0", color)
              .AddPlugin<Plugins::DataDispatcher<std::string>>()
              .RegisterGatherer([&]() { return TeamScore(); });
    }

    void LoadPlayers() const
    {
      using namespace ApUI;
      using namespace ApUI::Widgets;

      const auto color = m_team->EmpireColor();
      for(const auto &player : *m_team)
      {
        auto &row = m_table->CreateRow(player->uuid);
        row["Name"].SetValues(player->player_name, color);

        row["Total Points"]
            .AddPlugin<Plugins::DataDispatcher<std::string>>()
            .RegisterGatherer([&player](){ return fmt::to_string(player->total_score); });

        auto &net_score_row = row["Net Score"];
        net_score_row
            .AddPlugin<Plugins::DataDispatcher<std::string>>()
            .RegisterGatherer([&player, &net_score_row]() {
              net_score_row.Color = player->ScoreColor();
              return fmt::to_string(player->net_score);
            });

        row["Kills"]
          .AddPlugin<Plugins::DataDispatcher<std::string>>()
          .RegisterGatherer([&player]() { return fmt::to_string(player->kill_count); });

        row["Deaths"]
          .AddPlugin<Plugins::DataDispatcher<std::string>>()
          .RegisterGatherer([&player]() { return fmt::to_string(player->death_count); });

        auto &kill_death_row = row["KD"];
        kill_death_row
            .AddPlugin<Plugins::DataDispatcher<std::string>>()
            .RegisterGatherer([&player, &kill_death_row]() {
              kill_death_row.Color = player->KDColor();
              return fmt::format("{:.2f}", player->KillDeathAverage());
            });
      }
    }

    [[nodiscard]] std::string TeamScore() const
    {
      return fmt::format("Score {}", m_team->GetScore());
    }

  public:
    ApCore::Planetside::Team *m_team;
    ApUI::Widgets::Layout::Group *m_header;
    ApUI::Widgets::Tables::Table *m_table;

  private:
    bool m_team_loaded { false };
  };

  ScoreContent::ScoreContent() : TeamManager(5)
  {
    RegisterTeam(0, "vco");
    RegisterTeam(1, "GSLD");
    RegisterTeam(2, "HELP");
    RegisterTeam(3, "h0ur");
    RegisterTeam(4, "SKL");
    RecreateTeams();
    TeamManager.StartTrackingTeams();
  }

  void ScoreContent::ResizeTeams(int size)
  {
    TeamManager.SetSize(size);
    RecreateTeams();
  }

  void ScoreContent::RegisterTeam(int idx, const std::string &tag)
  {
    TeamManager.RegisterTeam(idx, tag);
//    RecreateTeams();
  }

  void ScoreContent::RecreateTeams()
  {
    using namespace ApUI;
    using namespace ApUI::Widgets;

    RemoveAllWidgets();
    CreateWidget<Layout::Dummy>(ImVec2(-FLT_MIN, 25.0f));
    for(int i = 0; i < TeamManager.size(); i++)
    {
      if(PRESENT_PTR(TeamManager[i]))
      {
        CreateWidget<TeamTable>(TeamManager[i].get());
      }

      if((i+1) < TeamManager.size())
      {
        CreateWidget<Layout::NewLine>();
        CreateWidget<Layout::Separator>();
        CreateWidget<Layout::NewLine>();
      }
    }
  }

  void ScoreContent::_Draw_Impl()
  {
    DrawWidgets();
  }
}