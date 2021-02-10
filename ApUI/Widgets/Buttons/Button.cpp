#include "Button.hpp"

namespace ApUI::Widgets::Buttons
{
  Button::Button(const std::string& label, bool enabled)
    : Button(label, AutoSizeBtn(label.c_str()), enabled)
    {}

  Button::Button(std::string label, ImVec2 size, bool enabled)
    : label(std::move(label))
  {
    SetSize(size);
    SetFlags(ImGuiButtonFlags_None);
    this->enabled = enabled;
  }

  void Button::_Draw_Impl()
  {
    if(ImGui::ButtonEx(label.c_str(), GetSize(), GetFlags()))
    {
      ClickEvent.Invoke();
    }
  }
}