#ifndef APUI_WIDGETS_BUTTONS_ABUTTON_HPP
#define APUI_WIDGETS_BUTTONS_ABUTTON_HPP

#include <ApTools/Eventing/Event.hpp>
#include <ApUI/Widgets/AWidget.hpp>
#include <ApUI/Plugins/ITransformable.hpp>

namespace ApUI::Widgets::Buttons
{
  class AButton : public AWidget, public Plugins::ITransformable
  {
  protected:
    void _Draw_Impl() override = 0;

    static ImVec2 AutoSizeBtn(const std::string &label, float mul_pad = 4.0f)
    {
      const ImGuiStyle& style = ImGui::GetCurrentContext()->Style;
      auto label_size         = ImGui::CalcTextSize(label.c_str());
      return ImVec2(label_size.x + style.FramePadding.x * mul_pad, label_size.y + style.FramePadding.y * mul_pad);
    }

  public:
    ApTools::Eventing::Event<> ClickEvent;
  };
}

#endif // APUI_WIDGETS_BUTTONS_ABUTTON_HPP
