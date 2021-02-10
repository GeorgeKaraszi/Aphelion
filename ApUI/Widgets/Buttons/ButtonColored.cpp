#include "ButtonColored.hpp"

namespace ApUI::Widgets::Buttons
{
  ButtonColored::ButtonColored(
      const char *label,
      const Types::Color &bg_color,
      const Types::Color &fg_color,
      bool enabled
  )
    : ButtonColored(label, AutoSizeBtn(label), bg_color, fg_color, enabled)
  {}

  ButtonColored::ButtonColored(
      const char* label,
      ImVec2 size,
      const Types::Color &bg_color,
      const Types::Color &fg_color,
      bool enabled
  )
    : label(label), bg_color(bg_color), fg_color(fg_color), enabled(enabled)
  {
    SetSize(size);
    SetFlags(ImGuiButtonFlags_NoNavFocus);
  }

  void ButtonColored::_Draw_Impl()
  {
    ImVec4 background_color(bg_color.ToImVec4());
    ImVec4 foreground_color(fg_color.ToImVec4());

    ImGui::PushStyleColor(ImGuiCol_Button,        background_color);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, background_color);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  background_color);
    ImGui::PushStyleColor(ImGuiCol_Text,          foreground_color);

    if(ImGui::ButtonEx(label.c_str(), GetSize(), GetFlags()))
    {
      ClickEvent.Invoke();
    }

    ImGui::PopStyleColor(4);
  }
}