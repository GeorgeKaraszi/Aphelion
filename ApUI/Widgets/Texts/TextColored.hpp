#ifndef APUI_WIDGETS_TEXTS_TEXTCOLORED_HPP
#define APUI_WIDGETS_TEXTS_TEXTCOLORED_HPP

#include <ApUI/Widgets/AWidget.hpp>
#include <ApUI/Types/Color.hpp>

namespace ApUI::Widgets::Texts
{
  class TextColored : public AWidget
  {
  public:
    TextColored(std::string text, const Types::Color& color);
  protected:
    void _Draw_Impl() override;
  private:
    std::string m_text;
    Types::Color m_color;
  };
}
#endif //APUI_WIDGETS_TEXTS_TEXTCOLORED_HPP
