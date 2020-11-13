#ifndef APUI_WIDGETS_LAYOUT_NEWLINE_HPP
#define APUI_WIDGETS_LAYOUT_NEWLINE_HPP

#include <ApUI/Widgets/AWidget.hpp>

namespace ApUI::Widgets::Layout
{
  class NewLine : public AWidget
  {
  protected:
    void _Draw_Impl() override
    {
      ImGui::NewLine();
    }
  };
}

#endif //APUI_WIDGETS_LAYOUT_NEWLINE_HPP
