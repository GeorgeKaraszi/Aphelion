#ifndef APUI_WIDGETS_DATAWIDGET_HPP
#define APUI_WIDGETS_DATAWIDGET_HPP

#include "AWidget.hpp"

namespace ApUI::Widgets
{
  template<typename T>
  class DataWidget : public AWidget
  {
  public:
    explicit DataWidget(T& data) : m_data(data) {}

    void Draw() override;
    void NotifyChange();

  private:
    T& m_data;
  };

  template<typename T>
  inline void DataWidget<T>::Draw()
  {
    if (enabled)
    {
      TRY_GATHER(T, m_data)
      AWidget::Draw();
      TRY_PROVIDE(T, m_data)
    }
  }

  template<typename T>
  inline void DataWidget<T>::NotifyChange()
  {
    TRY_NOTIFY_CHANGE(T);
  }
}

#endif //APUI_WIDGETS_DATAWIDGET_HPP
