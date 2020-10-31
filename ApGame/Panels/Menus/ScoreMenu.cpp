#include "ScoreMenu.hpp"
#include <ApUI/Widgets/Buttons/ButtonColored.hpp>

namespace ApGame::Panels::Menus
{
  ScoreMenu::ScoreMenu(const std::string &title, bool opened)
  : ApUI::Panels::PanelWindow(title, opened)
  {
    using namespace ApUI::Types;
    using namespace ApUI::Widgets::Buttons;
    m_scores = &CreateWidget<ApUI::Widgets::Columns::Column>(false);

    WidgetContainer *rows;

    rows = &m_scores->CreateColumn<ButtonColored>("Outfit TR Name", m_column_size, Color::Faction_TR);
    rows->CreateWidget<ButtonColored>("Left 1", m_column_size, Color::Faction_TR);
    rows->CreateWidget<ButtonColored>("Left 2", m_column_size, Color::Faction_TR);
    rows->CreateWidget<ButtonColored>("Left 3", m_column_size, Color::Faction_TR);

    rows = &m_scores->CreateColumn<ButtonColored>("Outfit NC Name", m_column_size, Color::Faction_NC);
    rows->CreateWidget<ButtonColored>("Right 1", m_column_size, Color::Faction_NC);
    rows->CreateWidget<ButtonColored>("Right 2", m_column_size, Color::Faction_NC);
    rows->CreateWidget<ButtonColored>("Right 3", m_column_size, Color::Faction_NC);
  }

  void ScoreMenu::AddItem(COLUMN_SIDE side, const char *text, const ApUI::Types::Color &bg)
  {
    m_scores->GetColumn(side)->CreateWidget<ApUI::Widgets::Buttons::ButtonColored>(text, m_column_size, bg);
  }
}
