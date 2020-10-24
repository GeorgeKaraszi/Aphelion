#ifndef APUI_WIDGETS_WIDGETCONTAINER_HPP
#define APUI_WIDGETS_WIDGETCONTAINER_HPP

#include <ApUI/Widgets/AWidget.hpp>

namespace ApUI::Widgets
{
  class WidgetContainer
  {
  public:
    std::vector<AWidget*> &GetWidgets();
    void RemoveWidget(AWidget &target);
    void RemoveAllWidgets();

    template<typename T, typename ... Args>
    T& CreateWidget(Args&&...args);

    void GarbageCollect();
    void DrawWidgets();


  protected:
    std::vector<AWidget*> m_widgets;
  };
}

#endif // APUI_WIDGETS_WIDGETCONTAINER_HPP
