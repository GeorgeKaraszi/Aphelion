#include "Table.hpp"
#include <ApUI/Widgets/Texts/TextColored.hpp>
#include <algorithm>

namespace ApUI::Widgets::Tables
{
  Table::Table(const char* tbl_id, const TableOptions &options)
  : Layout::Group(tbl_id), Options(options)
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
    auto row = FindRow(row_id);

    if(PRESENT_PTR(row))
    {
      return *row;
    }

    return CreateWidget<Row>(row_id, this);
  }

  void Table::_Draw_Impl()
  {
    auto table = ImGui::BeginTable(
        widget_id.c_str(),
        (int)Columns.size(),
        Options.TableFlags,
        Options.OuterSide,
        Options.InnerWidth
    );

    if(table)
    {
      if (Options.DisplayHeaders)
      {
        for (auto &column : Columns)
        {
          ImGui::TableSetupColumn(column.c_str(), Options.ColumnFlags);
        }

        ImGui::TableHeadersRow();
      }

      DrawWidgets();
      ImGui::EndTable();
    }
  }

  void Table::UniqueColumns()
  {
    auto it = std::unique(Columns.begin(), Columns.end());
    Columns.resize(std::distance(Columns.begin(), it));
  }

  Row *Table::FindRow(const std::string &row_id)
  {
    return reinterpret_cast<Row*>(FindWidget(row_id));
  }
}