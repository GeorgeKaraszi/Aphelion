#include "TextColored.hpp"

#include <utility>

namespace ApUI::Widgets::Texts
{
  TextColored::TextColored(const std::string &content, const Types::Color &color)
  : AText(content), Color(color)
  {}

  void TextColored::SetValues(std::string text, const Types::Color &color)
  {
    Content = std::move(text);
    Color   = color;
  }

  void TextColored::_Draw_Impl()
  {
    ImGui::TextColored(Color.ToImColor(), "%s", Content.c_str());
  }
}
