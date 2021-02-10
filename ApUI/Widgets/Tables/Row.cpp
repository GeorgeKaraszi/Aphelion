#include "Row.hpp"
#include "Table.hpp"
#include <utility>

namespace ApUI::Widgets::Tables
{
  Row::Row(std::string row_id, Table* table)
  : RowID(std::move(row_id)), m_table(table)
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
    for(auto &key : m_table->Columns)
    {
      ImGui::TableNextColumn();
      FindOrCreateColumnData(key).Draw();
    }
  }
}