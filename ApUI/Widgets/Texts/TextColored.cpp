#include "TextColored.hpp"

#include <utility>

namespace ApUI::Widgets::Texts
{
  TextColored::TextColored(const std::string &content, const Types::Color &color)
  : AText(content), Color(color)
  {}

  TextColored& TextColored::SetValues(std::string text, const Types::Color &color)
  {
    Content = std::move(text);
    Color   = color;
    return *this;
  }

  void TextColored::_Draw_Impl()
  {
    ImGui::TextColored(Color.ToImColor(), "%s", Content.c_str());
  }
}
