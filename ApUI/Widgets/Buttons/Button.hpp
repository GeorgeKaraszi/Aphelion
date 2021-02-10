#ifndef APUI_WIDGETS_BUTTONS_BUTTON_HPP
#define APUI_WIDGETS_BUTTONS_BUTTON_HPP

#include "AButton.hpp"

namespace ApUI::Widgets::Buttons
{
  class Button : public AButton
  {
  public:
    Button(const std::string& label, bool enabled = true);
    Button(std::string label, ImVec2 size, bool enabled = true);

  protected:
    void _Draw_Impl() override;

  public:
    std::string label;
  };
}

#endif //APUI_WIDGETS_BUTTONS_BUTTON_HPP
