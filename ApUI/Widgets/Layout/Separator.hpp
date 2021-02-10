#ifndef APUI_WIDGETS_LAYOUT_SEPARATOR_HPP
#define APUI_WIDGETS_LAYOUT_SEPARATOR_HPP

#include <ApUI/Widgets/AWidget.hpp>

namespace ApUI::Widgets::Layout
{
  class Separator : public AWidget
  {
  protected:
    void _Draw_Impl() override
    {
      ImGui::Separator();
    }
  };
}

#endif //APUI_WIDGETS_LAYOUT_SEPARATOR_HPP
