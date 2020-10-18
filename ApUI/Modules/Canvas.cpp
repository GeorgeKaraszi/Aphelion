#include "Canvas.hpp"

namespace ApUI::Modules
{
  void Canvas::Draw()
  {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for(auto &panel : m_panels)
    {
      panel.get().Draw();
    }

    ImGui::Render();
  }

  void Canvas::AddPanel(Panels::APanel &p_panel)
  {
    m_panels.push_back(std::ref(p_panel));
  }

  void Canvas::RemovePanel(Panels::APanel &p_panel)
  {
    m_panels.erase(std::remove_if(m_panels.begin(), m_panels.end(), [&p_panel](std::reference_wrapper<Panels::APanel>& p_item)
    {
      return &p_panel == &p_item.get();
    }));
  }

  void Canvas::RemoveAllPanels()
  {
    m_panels.clear();
  }
}