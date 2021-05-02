#include "Row.hpp"
#include "Table.hpp"
#include <utility>

namespace ApUI::Widgets::Tables
{
  Row::Row(const std::string& row_id, Table* table)
  : RowID(row_id), m_table(table), Layout::Group(row_id.c_str())
  {}

  Texts::TextColored &Row::operator[](const std::string &key)
  {
    return FindOrCreateColumnData(key);
  }

  Texts::TextColored &Row::FindOrCreateColumnData(const std::string &key)
  {
    if(m_data.find(key) == m_data.end())
    {
      auto columns = &m_table->Columns;
      auto it      = std::find(columns->begin(), columns->end(), key);
      assert(it != columns->end() && "Key does not exists in table!");

      m_data[key] = &CreateWidget<Texts::TextColored>("");
    }

    return *m_data[key];
  }

  void Row::_Draw_Impl()
  {
    ImGui::TableNextRow();

    for(int i = 0; i < m_table->Columns.size(); i++)
    {
      ImGui::TableSetColumnIndex(i);
      FindOrCreateColumnData(m_table->Columns[i]).Draw();
    }
  }
}