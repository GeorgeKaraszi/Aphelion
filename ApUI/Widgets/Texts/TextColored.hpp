#ifndef APUI_WIDGETS_TEXTS_TEXTCOLORED_HPP
#define APUI_WIDGETS_TEXTS_TEXTCOLORED_HPP

#include "AText.hpp"
#include <ApUI/Types/Color.hpp>

namespace ApUI::Widgets::Texts
{
  class TextColored : public AText
  {
  public:
    explicit TextColored(const std::string &content, const Types::Color& color = Types::Color::White);
    TextColored &SetValues(std::string content, const Types::Color& color);
  protected:
    void _Draw_Impl() override;
  public:
    Types::Color Color;
  };
}
#endif //APUI_WIDGETS_TEXTS_TEXTCOLORED_HPP
