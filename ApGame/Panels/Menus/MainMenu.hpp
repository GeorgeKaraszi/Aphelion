#ifndef APGAME_PANELS_MENUS_MAINMENU_HPP
#define APGAME_PANELS_MENUS_MAINMENU_HPP

#include <ApUI/Panels/PanelWindow.hpp>
#include <ApUI/Widgets/Layout/Group.hpp>

#pragma comment(lib, "ApUI.lib")
namespace ApGame::Panels::Menus
{
  class MainMenu : public ApUI::Panels::PanelWindow
  {
  public:
    MainMenu(const std::string &title, bool opened);
  private:
    ApUI::Widgets::Layout::Group *m_buttons;
  };
}

#endif // APGAME_PANELS_MENUS_MAINMENU_HPP
