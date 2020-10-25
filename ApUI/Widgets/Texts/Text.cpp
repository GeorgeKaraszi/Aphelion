#include "Text.hpp"

namespace ApUI::Widgets::Texts
{
  Text::Text(std::string text) : m_text(std::move(text))
  {}

  void Text::_Draw_Impl()
  {
    ImGui::Text("%s", m_text.c_str());
  }
}
