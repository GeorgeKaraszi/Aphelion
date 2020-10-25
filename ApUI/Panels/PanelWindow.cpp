#include "PanelWindow.hpp"

namespace ApUI::Panels
{
  PanelWindow::PanelWindow(std::string name, bool open)
  : name(std::move(name)), m_opened(open)
  {}

  PanelWindow::PanelWindow(std::string name, ImVec2 minSize, ImVec2 maxSize, bool open)
  : name(std::move(name)), minSize(minSize), maxSize(maxSize), m_opened(open)
  {}

  void PanelWindow::Open()
  {
    if(!m_opened)
    {
      m_opened = true;
      OpenEvent.Invoke();
    }
  }

  void PanelWindow::Close()
  {
    if(m_opened)
    {
      m_opened = false;
      CloseEvent.Invoke();
    }
  }

  void PanelWindow::SetOpen(bool open)
  {
    m_opened = !open;
    open ? Open() : Close();
  }

  bool PanelWindow::IsOpen() const
  {
    return m_opened;
  }

  bool PanelWindow::IsHovered() const
  {
    return m_hovered;
  }

  void PanelWindow::SetPosition(ImVec2 position)
  {
    m_position = position;
  }

  void PanelWindow::SetSize(ImVec2 size)
  {
    m_size = size;
  }

  ImVec2 PanelWindow::GetPosition() const
  {
    return m_position;
  }

  ImVec2 PanelWindow::GetSize() const
  {
    return m_size;
  }

  void PanelWindow::Update()
  {
    ImVec2 result(m_size.x / 2.0f, m_size.y / 2.0f);
    ImVec2 offsetPosition(result.x + m_position.x, result.y + m_position.y);

    ImGui::SetWindowSize(m_size, ImGuiCond_Always);
    ImGui::SetWindowPos(offsetPosition, ImGuiCond_FirstUseEver);

    m_position = ImGui::GetWindowPos();
    m_size     = ImGui::GetWindowSize();
  }

  void PanelWindow::_Draw_Impl()
  {
    // Apply Window Flags here
    int window_flags = ImGuiWindowFlags_None;

    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    if(ImGui::Begin(name.c_str(), &m_opened, window_flags))
    {
      m_hovered = ImGui::IsWindowHovered();

      if(!m_opened)
      {
        CloseEvent.Invoke();
      }

//      Update();
      DrawWidgets();
    }

    ImGui::End();
  }
}

