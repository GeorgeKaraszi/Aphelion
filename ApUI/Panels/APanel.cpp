#include <algorithm>
#include <string>
#include "APanel.hpp"

uint64_t ApUI::Panels::APanel::__PANEL_ID_INCREMENT = 0;

namespace ApUI::Panels
{
  APanel::APanel(bool open) : m_opened(open)
  {
    m_panelID = "##" + std::to_string(__PANEL_ID_INCREMENT++);
  }

  void APanel::Open()
  {
    if(!m_opened)
    {
      m_opened = true;
      OpenEvent.Invoke();
    }
  }

  void APanel::Close()
  {
    if(m_opened)
    {
      m_opened = false;
      CloseEvent.Invoke();
    }
  }

  void APanel::SetOpen(bool open)
  {
    m_opened = !open;
    open ? Open() : Close();
  }

  bool APanel::IsOpen() const
  {
    return m_opened;
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

  void APanel::_Draw_Impl()
  {
    DrawWidgets();
  }
}