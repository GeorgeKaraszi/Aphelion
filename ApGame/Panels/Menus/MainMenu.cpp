#include <ApUI/Widgets/Texts/TextColored.hpp>
#include <ApUI/Widgets/Buttons/Button.hpp>
#include <ApUI/Widgets/WidgetContainer.hpp>
#include "MainMenu.hpp"

namespace ApGame::Panels::Menus
{
  MainMenu::MainMenu(const std::string &title, bool opened)
    : ApUI::Panels::PanelWindow(title, opened)
  {
    m_buttons = &CreateWidget<ApUI::Widgets::Layout::Group>();
    &m_buttons->CreateWidget<ApUI::Widgets::Buttons::Button>("Test", ImVec2(100, 100));
    m_buttons->CreateWidget<ApUI::Widgets::Buttons::Button>("Test 2", ImVec2(100, 100));
    m_buttons->CreateWidget<ApUI::Widgets::Texts::TextColored>("COMING SOON", ApUI::Types::Color::Faction_NC);
  }
}