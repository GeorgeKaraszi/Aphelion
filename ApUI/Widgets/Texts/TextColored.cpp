#include "TextColored.hpp"

namespace ApUI::Widgets::Texts
{
  TextColored::TextColored(std::string text, const Types::Color &color)
  : m_text(std::move(text)), m_color(color)
  {}

  void TextColored::_Draw_Impl()
  {
    ImGui::TextColored(m_color.ToImColor(), "%s", m_text.c_str());
  }
}
