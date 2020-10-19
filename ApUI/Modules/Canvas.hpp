#ifndef APUI_MODULES_CANVAS_HPP
#define APUI_MODULES_CANVAS_HPP

#include <ApUI/Plugins/IDrawable.hpp>
#include <ApUI/Panels/APanel.hpp>
#include <ApUI/ImGui/imgui.h>
#include <ApUI/ImGui/imgui_impl_dx11.h>
#include <ApUI/ImGui/imgui_impl_win32.h>

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
