#include <algorithm>
#include <string>
#include "APanel.hpp"

uint64_t ApUI::Panels::APanel::__PANEL_ID_INCREMENT = 0;

namespace ApUI::Panels
{
  APanel::APanel()
  {
    m_panelID = "##" + std::to_string(__PANEL_ID_INCREMENT++);
  }

  void APanel::Draw()
  {
    if(enabled)
    {
      _Draw_Impl();
    }
  }

  const std::string &APanel::GetPanelID() const
  {
    return m_panelID;
  }
}