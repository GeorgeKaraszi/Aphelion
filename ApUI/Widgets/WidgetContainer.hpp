#ifndef APUI_WIDGETS_WIDGETCONTAINER_HPP
#define APUI_WIDGETS_WIDGETCONTAINER_HPP

#include <ApUI/Widgets/AWidget.hpp>

namespace ApUI::Widgets
{
  class WidgetContainer
  {
  public:
    ~WidgetContainer();
    AWidget* operator[](int idx);
    std::vector<AWidget*> &GetWidgets();
    AWidget *FindWidget(const std::string &widget_id);
    void RemoveWidget(AWidget &target);
    void RemoveAllWidgets();

    void GarbageCollect();
    void DrawWidgets();

    template<typename T, typename ...Args>
    T& CreateWidget(Args&&...args)
    {
      m_widgets.push_back(new T(std::forward<Args>(args)...));
      T &widget = *reinterpret_cast<T*>(m_widgets.back());
      widget.SetParent(this);

      return widget;
    }

  protected:
    std::vector<AWidget*> m_widgets;
  };
}

#endif // APUI_WIDGETS_WIDGETCONTAINER_HPP
