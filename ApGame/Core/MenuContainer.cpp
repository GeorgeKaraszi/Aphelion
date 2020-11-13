#include <ApUI/Widgets/Buttons/ButtonColored.hpp>
#include <ApUI/Widgets/Buttons/Button.hpp>
#include <ApUI/Widgets/Columns/Column.hpp>
#include <ApUI/Widgets/Windows/ChildWindow.hpp>
#include <ApUI/Widgets/Layout/NewLine.hpp>
#include <ApInclude/pch.hpp>
#include "MenuContainer.hpp"

#define SET_ACTIVE(body, menu_item) SetCurrentPanel(body); m_menu_bar->SetActiveItem(menu_item);

namespace ApGame::Core
{
  class MenuBar : public ApUI::Widgets::Layout::Group
  {
  public:
    MenuBar()
    {
      using namespace ApUI::Types;
      using namespace ApUI::Widgets;
      using namespace ApUI::Widgets::Buttons;

      auto size = ImVec2(-FLT_MIN, 30.0f);
      m_group  = &CreateWidget<Columns::Column>();
      Score    = &m_group->CreateWidget<ButtonColored>("Score", size, Color::Yellow, Color::Red);
      Stats    = &m_group->CreateWidget<ButtonColored>("Stats", size, Color::Yellow, Color::Red);
      Teams    = &m_group->CreateWidget<ButtonColored>("Teams", size, Color::Yellow, Color::Red);
      Settings = &m_group->CreateWidget<ButtonColored>("Settings", size, Color::Yellow, Color::Red);
      SetActiveItem(Score);

      CreateWidget<Layout::NewLine>();
    }

    void SetActiveItem(ApUI::Widgets::Buttons::ButtonColored *selected)
    {
      ApplyInactiveStyle();
      SelectedItem = selected;
      ApplyActiveStyle();
    }

    void ApplyActiveStyle() const
    {
      if(BLANK_PTR(SelectedItem)) return;
      SelectedItem->fg_color = ApUI::Types::Color::Yellow;
      SelectedItem->bg_color = ApUI::Types::Color::Red;
    }

    void ApplyInactiveStyle() const
    {
      if(BLANK_PTR(SelectedItem)) return;
      SelectedItem->fg_color = ApUI::Types::Color::Red;
      SelectedItem->bg_color = ApUI::Types::Color::Yellow;
    }

  public:
    ApUI::Widgets::Buttons::ButtonColored *Score;
    ApUI::Widgets::Buttons::ButtonColored *Stats;
    ApUI::Widgets::Buttons::ButtonColored *Teams;
    ApUI::Widgets::Buttons::ButtonColored *Settings;
    ApUI::Widgets::Buttons::ButtonColored *SelectedItem = nullptr;
  private:
    ApUI::Widgets::Columns::Column *m_group;
  };

  class RenderBody : public ApUI::Widgets::Layout::Group
  {
  public:
    explicit RenderBody(const char* label)
    {
      auto size = ImVec2(-FLT_MIN, 30.0f);
      auto test = &CreateWidget<ApUI::Widgets::Buttons::Button>("Test", size);
      CreateWidget<ApUI::Widgets::Buttons::Button>("Results", size);
      CreateWidget<ApUI::Widgets::Buttons::Button>(label, size);

      test->lineBreak = false;
    }
  };

  MenuContainer::MenuContainer() : ApUI::Panels::PanelWindow("Main Window")
  {
    using namespace ApUI::Widgets;

    m_menu_bar      = &CreateWidget<MenuBar>();
    m_body_window   = &CreateWidget<Windows::ChildWindow>("ChildBody", Windows::ApUIWindow_SizeByAvailableSpace);

    m_score_body    = &m_body_window->CreateWidget<Contents::ScoreContent>();
    m_stats_body    = &m_body_window->CreateWidget<RenderBody>("Stats Body");
    m_teams_body    = &m_body_window->CreateWidget<RenderBody>("Teams Body");
    m_settings_body = &m_body_window->CreateWidget<RenderBody>("Settings Body");

    m_stats_body->enabled    = false;
    m_teams_body->enabled    = false;
    m_settings_body->enabled = false;

    m_menu_bar->Score->ClickEvent    += [&] { SET_ACTIVE(m_score_body, m_menu_bar->Score) };
    m_menu_bar->Stats->ClickEvent    += [&] { SET_ACTIVE(m_stats_body, m_menu_bar->Stats) };
    m_menu_bar->Teams->ClickEvent    += [&] { SET_ACTIVE(m_teams_body, m_menu_bar->Teams) };
    m_menu_bar->Settings->ClickEvent += [&] { SET_ACTIVE(m_settings_body, m_menu_bar->Settings) };

    SetCurrentPanel(m_score_body);
  }

  void MenuContainer::Update()
  {
    ApUI::Panels::PanelWindow::Update();
    m_body_window->SetSize(ImGui::GetWindowSize() - ImGui::GetCursorPos());
  }

  void MenuContainer::SetCurrentPanel(ApUI::Widgets::AWidget *next_panel)
  {
    if(PRESENT_PTR(m_current_body))
      m_current_body->enabled = false;

    m_current_body          = next_panel;
    m_current_body->enabled = true;
    // Apply New Item styles
  }
}