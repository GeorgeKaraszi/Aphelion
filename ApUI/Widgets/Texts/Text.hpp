#ifndef APUI_WIDGETS_TEXTS_TEXT_HPP
#define APUI_WIDGETS_TEXTS_TEXT_HPP

#include <ApUI/Widgets/DataWidget.hpp>

namespace ApUI::Widgets::Texts
{
  class Text : public DataWidget<std::string>
  {
  public:
    Text(std::string text);
  protected:
    void _Draw_Impl() override;
  private:
    std::string m_text;
  };
}

#endif //APUI_WIDGETS_TEXTS_TEXT_HPP
