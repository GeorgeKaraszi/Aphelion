#include "PanelWindow.hpp"

namespace ApUI::Panels
{
  PanelWindow::PanelWindow(std::string name, bool open)
  : name(std::move(name)), APanel(open)
  {
    SetFlags(ImGuiWindowFlags_NoDecoration);
  }

  bool PanelWindow::IsHovered() const
  {
    return m_hovered;
  }

  void PanelWindow::Update()
  {
    ImGui::SetWindowPos(m_position, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(m_size, ImGuiCond_Always);
  }

  void PanelWindow::_Draw_Impl()
  {

    BeginStyle();
    if(ImGui::Begin(name.c_str(), &m_opened, m_flags))
    {
      m_hovered = ImGui::IsWindowHovered();

      if(!m_opened)
      {
        CloseEvent.Invoke();
      }

      Update();
      DrawWidgets();
    }

    ImGui::End();
    EndStyle();
  }
}

