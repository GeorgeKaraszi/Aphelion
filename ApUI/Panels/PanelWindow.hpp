#ifndef APUI_PANELS_PANELWINDOW_HPP
#define APUI_PANELS_PANELWINDOW_HPP

#include <ApUI/ImGui/imgui.h>
#include <ApUI/Plugins/ITransformable.hpp>
#include <ApUI/Plugins/Styleable.hpp>
#include "APanel.hpp"

namespace ApUI::Panels
{
  class PanelWindow : public APanel, public Plugins::ITransformable, public Plugins::Styleable
  {
  public:
    explicit PanelWindow(std::string name, bool open = true);

    [[nodiscard]]
    bool IsHovered() const;

  protected:
    virtual void Update() override;
    void _Draw_Impl() override;

  public:
    std::string name;
    ImVec2 minSize = { 0, 0 };
    ImVec2 maxSize = { 10000.0f, 10000.0f };

  private:
    bool m_hovered = false;

  };
}

#endif //APUI_PANELS_PANELWINDOW_HPP
