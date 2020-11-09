#ifndef APUI_WIDGETS_WINDOWS_CHILDWINDOW_HPP
#define APUI_WIDGETS_WINDOWS_CHILDWINDOW_HPP

#include <ApUI/ImGui/imgui.h>
#include <ApUI/Plugins/ITransformable.hpp>
#include <ApUI/Plugins/Styleable.hpp>
#include <ApTools/Eventing/Event.hpp>
#include <ApUI/Widgets/WidgetContainer.hpp>

namespace ApUI::Widgets::Windows
{
  class ChildWindow : public AWidget, public WidgetContainer, public Plugins::ITransformable
  {
  public:
    ChildWindow(std::string name, ImVec2 size, bool boarder = false);

  protected:
    void _Draw_Impl() override;

  public:
    std::string name;
  private:
    bool m_boarder = false;
  };
}

#endif // APUI_WIDGETS_WINDOWS_CHILDWINDOW_HPP
