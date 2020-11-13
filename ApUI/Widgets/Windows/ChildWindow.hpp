#ifndef APUI_WIDGETS_WINDOWS_CHILDWINDOW_HPP
#define APUI_WIDGETS_WINDOWS_CHILDWINDOW_HPP

#include <ApUI/ImGui/imgui.h>
#include <ApUI/Plugins/ITransformable.hpp>
#include <ApUI/Plugins/Styleable.hpp>
#include <ApTools/Eventing/Event.hpp>
#include <ApUI/Widgets/WidgetContainer.hpp>

namespace ApUI::Widgets::Windows
{
  enum ResizeWindowFlags { ApUIWindow_NoChange, ApUIWindow_SizeByAvailableSpace };
  class ChildWindow : public AWidget, public WidgetContainer, public Plugins::ITransformable
  {
  public:
    explicit ChildWindow(
        std::string name,
        ResizeWindowFlags size_flag = ApUIWindow_NoChange,
        ImVec2 size                 = ImVec2(-FLT_MIN, FLT_MAX)
    );

  protected:
    void Update() override;
    void _Draw_Impl() override;

  public:
    std::string name;
    ResizeWindowFlags ResizeFlag;
    bool ShowBoarder = false;
  };
}

#endif // APUI_WIDGETS_WINDOWS_CHILDWINDOW_HPP
