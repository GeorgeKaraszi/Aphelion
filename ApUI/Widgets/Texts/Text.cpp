#include "Text.hpp"

namespace ApUI::Widgets::Texts
{
  Text::Text(std::string text)
  : DataWidget(m_text),
    m_text(std::move(text))
  {}

  void Text::_Draw_Impl()
  {
    ImGui::TextUnformatted(m_text.c_str());
  }
}
