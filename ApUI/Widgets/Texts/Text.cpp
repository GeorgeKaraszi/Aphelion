#include "Text.hpp"

namespace ApUI::Widgets::Texts
{
  Text::Text(const std::string &content) : AText(content)
  {}

  void Text::_Draw_Impl()
  {
    ImGui::TextUnformatted(Content.c_str());
  }
}
