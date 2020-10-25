#include "Button.hpp"

namespace ApUI::Widgets::Buttons
{
  Button::Button(std::string label, ImVec2 size, bool enabled)
    : label(std::move(label)), size(size), enabled(enabled)
  {}

  void Button::_Draw_Impl()
  {
    if(ImGui::Button(label.c_str(), size))
    {
      ClickEvent.Invoke();
    }
  }
}