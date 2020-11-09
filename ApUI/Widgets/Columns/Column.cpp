#include "Column.hpp"

namespace ApUI::Widgets::Columns
{
  Column::Column(bool boarder) : m_boarder(boarder)
  {}

  void Column::_Draw_Impl()
  {
    auto col_size = m_widgets.size();

    ImGui::Columns(col_size, m_widget_id.c_str(), m_boarder);

    for(int i = 0; i < col_size; i++)
    {
      m_widgets[i]->Draw();

      if((i+1) < col_size)
      {
        ImGui::NextColumn();
      }
    }

    ImGui::EndColumns();
  }
}