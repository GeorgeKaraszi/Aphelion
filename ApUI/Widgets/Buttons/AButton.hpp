#ifndef APUI_WIDGETS_BUTTONS_ABUTTON_HPP
#define APUI_WIDGETS_BUTTONS_ABUTTON_HPP

#include <ApTools/Eventing/Event.hpp>
#include <ApUI/Widgets/AWidget.hpp>

namespace ApUI::Widgets::Buttons
{
  class AButton : public AWidget
  {
  protected:
    void _Draw_Impl() override = 0;
  public:
    ApTools::Eventing::Event<> ClickEvent;
  };
}

#endif // APUI_WIDGETS_BUTTONS_ABUTTON_HPP