#include <algorithm>
#include <ApInclude/macros.h>
#include "WidgetContainer.hpp"

namespace ApUI::Widgets
{
  std::vector<AWidget*> &WidgetContainer::GetWidgets()
  {
    return m_widgets;
  }

  void WidgetContainer::RemoveWidget(AWidget &target)
  {
    auto found = std::find_if(m_widgets.begin(), m_widgets.end(), [&target](AWidget* widget)
    {
      return widget == &target;
    });

    if(found != m_widgets.end())
    {
      delete *found;
      m_widgets.erase(found);
    }
  }

  void WidgetContainer::RemoveAllWidgets()
  {
    std::for_each(m_widgets.begin(), m_widgets.end(), [](AWidget *widget)
    {
      delete widget;
    });

    m_widgets.clear();
  }

  void WidgetContainer::GarbageCollect()
  {
    m_widgets.erase(std::remove_if(m_widgets.begin(), m_widgets.end(), [](AWidget* widget)
    {
      bool needs_removal = BLANK_PTR(widget) || widget->IsDestroyed();

      if(PRESENT_PTR(widget) && needs_removal)
      {
        delete widget;
      }

      return needs_removal;
    }), m_widgets.end());
  }

  void WidgetContainer::DrawWidgets()
  {
    GarbageCollect();

    for(AWidget *widget : m_widgets)
    {
      widget->Draw();
    }
  }
}