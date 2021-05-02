#include "Canvas.hpp"

namespace ApUI::Modules
{
  void Canvas::Draw()
  {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    #if DEBUG_MODE
      static bool demo = true;
      if(demo) ImGui::ShowDemoWindow(&demo);
    #endif

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
    auto position = std::find_if(
        m_panels.begin(),
        m_panels.end(),
        [&p_panel](std::reference_wrapper<Panels::APanel>& p_item) { return &p_panel == &p_item.get();}
    );

    if(position != m_panels.end())
    {
      m_panels.erase(position);
    }
  }

  void Canvas::RemoveAllPanels()
  {
    m_panels.clear();
  }

  void Canvas::ReplacePanelsWith(Panels::APanel &p_panel)
  {
    RemoveAllPanels();
    AddPanel(p_panel);
  }
}