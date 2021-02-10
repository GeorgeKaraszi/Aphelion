#ifndef APUI_WIDGETS_TEXTS_TEXT_HPP
#define APUI_WIDGETS_TEXTS_TEXT_HPP

#include "AText.hpp"

namespace ApUI::Widgets::Texts
{
  class Text : public AText
  {
  public:
    explicit Text(const std::string &content);
  protected:
    void _Draw_Impl() override;
  };
}

#endif //APUI_WIDGETS_TEXTS_TEXT_HPP
