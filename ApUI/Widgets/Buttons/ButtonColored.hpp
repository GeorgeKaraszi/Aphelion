#ifndef APUI_WIDGETS_BUTTONS_BUTTONCOLORED_HPP
#define APUI_WIDGETS_BUTTONS_BUTTONCOLORED_HPP

#include "AButton.hpp"
#include <ApUI/Types/Color.hpp>

namespace ApUI::Widgets::Buttons
{
  class ButtonColored : public AButton
  {
  public:
    ButtonColored(
        const char* label,
        ImVec2 size,
        const Types::Color &bg_color,
        const Types::Color &fg_color = Types::Color::White,
        bool enabled = true
    );

  protected:
    void _Draw_Impl() override;

  public:
    std::string  label;
    Types::Color bg_color;
    Types::Color fg_color;
    ImVec2 size;
    bool enabled;
  };
}

#endif //APUI_WIDGETS_BUTTONS_BUTTONCOLORED_HPP
