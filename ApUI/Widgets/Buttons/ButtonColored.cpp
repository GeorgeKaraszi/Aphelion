#include "ButtonColored.hpp"

namespace ApUI::Widgets::Buttons
{
  ButtonColored::ButtonColored(
      const char* label,
      ImVec2 size,
      const Types::Color &bg_color,
      const Types::Color &fg_color,
      bool enabled
  )
    : label(label), size(size), bg_color(bg_color), fg_color(fg_color), enabled(enabled)
  {}

  void ButtonColored::_Draw_Impl()
  {
    ImVec4 background_color(bg_color.ToImVec4());
    ImVec4 foreground_color(fg_color.ToImVec4());

    ImGui::PushStyleColor(ImGuiCol_Button,        background_color);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, background_color);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  background_color);
    ImGui::PushStyleColor(ImGuiCol_Text,          foreground_color);

    if(ImGui::ButtonEx(label.c_str(), size, ImGuiButtonFlags_NoNavFocus))
    {
      ClickEvent.Invoke();
    }

    ImGui::PopStyleColor(4);
  }
}