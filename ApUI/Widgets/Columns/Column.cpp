#include "Column.hpp"

namespace ApUI::Widgets::Columns
{
  Column::Column(bool boarder) : m_boarder(boarder)
  {}

  Column::~Column()
  {
    for(const auto& pair : m_columns)
    {
      delete pair.first;
    }

    m_columns.clear();
  }

  AWidget *Column::GetHeader(int position)
  {
    if(position > m_columns.size())
    {
      return nullptr;
    }

    return m_columns[position].first;
  }

  WidgetContainer *Column::GetColumn(int position)
  {
    if(position > m_columns.size())
    {
      return nullptr;
    }

    return &m_columns[position].second;
  }

  void Column::_Draw_Impl()
  {
    auto col_size = m_columns.size();

    ImGui::Columns(col_size, m_widget_id.c_str(), m_boarder);

    for(int i = 0; i < col_size; i++)
    {
      m_columns[i].first->Draw();
      m_columns[i].second.DrawWidgets();
      if((i+1) < col_size)
      {
        ImGui::NextColumn();
      }
    }

    ImGui::EndColumns();
  }
}