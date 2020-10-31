#ifndef APGAME_PANELS_MENUS_SCOREMENU_HPP
#define APGAME_PANELS_MENUS_SCOREMENU_HPP

#include <ApUI/Panels/PanelWindow.hpp>
#include <ApUI/Widgets/Columns/Column.hpp>
#include <ApUI/Types/Color.hpp>

#pragma comment(lib, "ApUI.lib")
namespace ApGame::Panels::Menus
{
  class ScoreMenu : public ApUI::Panels::PanelWindow
  {
  public:
    enum COLUMN_SIDE { LEFT = 0, RIGHT = 1 };
  public:
    ScoreMenu(const std::string &title, bool opened);
    void AddItem(COLUMN_SIDE side, const char *text, const ApUI::Types::Color &bg);

  private:
    ApUI::Widgets::Columns::Column *m_scores;
    ImVec2 m_column_size = ImVec2(-FLT_MIN, 30.0f);
  };
}

#endif //APGAME_PANELS_MENUS_SCOREMENU_HPP
