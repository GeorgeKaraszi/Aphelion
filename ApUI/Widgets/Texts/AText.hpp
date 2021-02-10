#ifndef APUI_WIDGETS_TEXTS_ATEXT_HPP
#define APUI_WIDGETS_TEXTS_ATEXT_HPP

#include <ApUI/Widgets/AWidget.hpp>
#include <ApUI/Widgets/DataWidget.hpp>
#include <utility>

namespace ApUI::Widgets::Texts
{
  class AText : public DataWidget<std::string>
  {
  public:
    explicit AText(std::string text = "")
    : DataWidget<std::string>(Content), Content(std::move(text))
    {}

  public:
    std::string Content;
  };
}

#endif //APUI_WIDGETS_TEXTS_ATEXT_HPP
