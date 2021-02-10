#ifndef APUI_WIDGETS_TABLES_TABLE_HPP
#define APUI_WIDGETS_TABLES_TABLE_HPP

#include <ApUI/Widgets/Layout/Group.hpp>
#include "Row.hpp"

namespace ApUI::Widgets::Tables
{
  class Table : public Layout::Group
  {
  public:
    explicit Table(
        ImGuiTableFlags tbl_flags       = 0,
        ImGuiTableColumnFlags col_flags = 0,
        const ImVec2& outer_size        = ImVec2(-FLT_MIN, 0),
        float inner_width               = 0.0f
      );

    void AddColumn(const std::string &name);
    void AddColumns(const std::vector<std::string> &names);
    Row &CreateRow(const std::string &row_id);
    Row *FindRow(const std::string &row_id);

  private:
    void _Draw_Impl() override;
    void UniqueColumns();

  public:
    ImGuiTableFlags TableFlags;
    ImGuiTableColumnFlags ColumnFlags;
    std::vector<std::string> Columns;

  private:
    ImVec2 m_outer_size;
    float m_inner_width;
  };
}

#endif //APUI_WIDGETS_TABLES_TABLE_HPP
