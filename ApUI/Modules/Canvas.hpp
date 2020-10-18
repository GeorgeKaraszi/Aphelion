#ifndef APUI_MODULES_CANVAS_HPP
#define APUI_MODULES_CANVAS_HPP

#include <Plugins/IDrawable.hpp>
#include <Panels/APanel.hpp>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

namespace ApUI::Modules
{
  class Canvas : public ApUI::Plugins::IDrawable
  {
  public:
    void Draw() override;
    void AddPanel(Panels::APanel &p_panel);
    void RemovePanel(Panels::APanel &p_panel);
    void RemoveAllPanels();

  private:
    std::vector<std::reference_wrapper<Panels::APanel>> m_panels;
  };
}

#endif //APUI_MODULES_CANVAS_HPP
