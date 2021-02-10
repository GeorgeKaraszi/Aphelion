#include "Table.hpp"
#include <ApUI/Widgets/Texts/TextColored.hpp>
#include <algorithm>

namespace ApUI::Widgets::Tables
{
  Table::Table(
      ImGuiTableFlags tbl_flags,
      ImGuiTableColumnFlags col_flags,
      const ImVec2& outer_size,
      float inner_width
  ) : TableFlags(tbl_flags), ColumnFlags(col_flags), m_outer_size(outer_size), m_inner_width(inner_width)
  {}

  void Table::AddColumn(const std::string &name)
  {
    Columns.push_back(name);
    UniqueColumns();
  }

  void Table::AddColumns(const std::vector<std::string> &names)
  {
    Columns.insert(Columns.end(), names.begin(), names.end());
    UniqueColumns();
  }

  Row &Table::CreateRow(const std::string &row_id)
  {
    return CreateWidget<Row>(row_id, this);
  }

  void Table::_Draw_Impl()
  {
    ImGui::BeginTable(widget_id.c_str(), Columns.size(), TableFlags, m_outer_size, m_inner_width);

    for(auto &column : Columns)
    {
      ImGui::TableSetupColumn(column.c_str(), ColumnFlags);
    }

    ImGui::TableHeadersRow();
    DrawWidgets();
    ImGui::EndTable();
  }

  void Table::UniqueColumns()
  {
    auto it = std::unique(Columns.begin(), Columns.end());
    Columns.resize(std::distance(Columns.begin(), it));
  }

  Row *Table::FindRow(const std::string &row_id)
  {
    auto found = std::find_if(m_widgets.begin(), m_widgets.end(), [&row_id](AWidget* widget)
    {
      Row *row = (Row*)widget;
      return row->RowID == row_id;
    });

    if(found != m_widgets.end())
    {
      return dynamic_cast<Row*>(*found);
    }

    return nullptr;
  }
}