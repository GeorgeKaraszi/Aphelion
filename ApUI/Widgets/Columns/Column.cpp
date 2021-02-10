#include "Column.hpp"

namespace ApUI::Widgets::Columns
{
  Column::Column(bool boarder) : m_boarder(boarder)
  {}

  void Column::_Draw_Impl()
  {
    auto col_size = m_widgets.size();

    if(col_size > 1)
    {
      ImGui::Columns(col_size, widget_id.c_str(), m_boarder);
    }

    for(int i = 0; i < col_size; i++)
    {
      m_widgets[i]->Draw();

      if((i+1) < col_size)
      {
        ImGui::NextColumn();
      }
    }

    if(col_size > 1)
    {
      ImGui::EndColumns();
    }
  }
}