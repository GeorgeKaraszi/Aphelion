#ifndef APUI_WIDGETS_LAYOUT_GROUP_HPP
#define APUI_WIDGETS_LAYOUT_GROUP_HPP

#include <ApUI/Widgets/WidgetContainer.hpp>

namespace ApUI::Widgets::Layout
{
  class Group : public AWidget, public WidgetContainer
  {
    using AWidget::AWidget;
  public:
    explicit Group(const char* widget_id) : AWidget(widget_id) {}
  protected:
    virtual void _Draw_Impl() override;
  };
}

#endif // APUI_WIDGETS_LAYOUT_GROUP_HPP
