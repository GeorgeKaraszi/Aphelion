#ifndef APGAME_CORE_MENUCONTAINER_HPP
#define APGAME_CORE_MENUCONTAINER_HPP

#include <ApUI/Panels/APanel.hpp>
#include <ApUI/Widgets/AWidget.hpp>
#include <ApUI/Panels/PanelWindow.hpp>
#include <ApUI/Widgets/Windows/ChildWindow.hpp>
#include <ApGame/Contents/ScoreContent.hpp>
#include <ApGame/Contents/SettingsContent.hpp>

#pragma comment(lib, "ApUI.lib")
namespace ApGame::Core
{
  class MenuBar;
  class MenuContainer : public ApUI::Panels::PanelWindow
  {
    using APanel = ApUI::Panels::APanel;
  public:
    MenuContainer();

  protected:
    void Update() override;
  private:
    void SetCurrentPanel(ApUI::Widgets::AWidget *next_panel);

  private:
    MenuBar *m_menu_bar;
    ApUI::Widgets::Windows::ChildWindow *m_body_window;
    Contents::ScoreContent      *m_score_body    = nullptr;
    Contents::SettingsContent   *m_settings_body = nullptr;
    ApUI::Widgets::AWidget      *m_stats_body    = nullptr;
    ApUI::Widgets::AWidget *m_teams_body         = nullptr;
    ApUI::Widgets::AWidget *m_selected_menu_item = nullptr;
    ApUI::Widgets::AWidget *m_current_body       = nullptr;
  };
}

#endif //APGAME_CORE_MENUCONTAINER_HPP
