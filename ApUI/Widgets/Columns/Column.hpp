#ifndef APUI_WIDGETS_COLUMNS_COLUMN_HPP
#define APUI_WIDGETS_COLUMNS_COLUMN_HPP

#include <ApUI/Widgets/Layout/Group.hpp>

namespace ApUI::Widgets::Columns
{
class Column : public Layout::Group
  {
  public:
    explicit Column(bool boarder = false);

  protected:
    void _Draw_Impl() override;

  private:
    bool m_boarder;
  };
}


#endif //APUI_WIDGETS_COLUMNS_COLUMN_HPP
