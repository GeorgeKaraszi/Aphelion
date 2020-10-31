#ifndef APUI_WIDGETS_COLUMNS_COLUMN_HPP
#define APUI_WIDGETS_COLUMNS_COLUMN_HPP

#include <ApTools/Eventing/Event.hpp>
#include <ApUI/Widgets/WidgetContainer.hpp>

namespace ApUI::Widgets::Columns
{
  class Column : public AWidget
  {
  public:
    explicit Column(bool boarder = false);
    ~Column();

    AWidget* GetHeader(int position);
    WidgetContainer* GetColumn(int position);

    template<typename T, typename ...Args>
    WidgetContainer& CreateColumn(Args&&...args)
    {
      m_columns.push_back(std::make_pair(new T(std::forward<Args>(args)...), WidgetContainer()));
      return m_columns.back().second;
    }

  protected:
    void _Draw_Impl() override;

  private:
    bool m_boarder;
    std::vector<std::pair<AWidget*, WidgetContainer>> m_columns;
  };
}


#endif //APUI_WIDGETS_COLUMNS_COLUMN_HPP
