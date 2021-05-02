#ifndef APUI_WIDGETS_TABLES_TABLE_HPP
#define APUI_WIDGETS_TABLES_TABLE_HPP

#include <ApUI/Widgets/Layout/Group.hpp>
#include "Row.hpp"

namespace ApUI::Widgets::Tables
{
  struct alignas(32) TableOptions
  {
    ImGuiTableFlags TableFlags        = 0;
    ImGuiTableColumnFlags ColumnFlags = 0;
    ImVec2 OuterSide                  = ImVec2(-FLT_MIN, 0);
    float InnerWidth                  = 0.0f;
    bool DisplayHeaders               = true;
  };

  class Table : public Layout::Group
  {
  public:
    explicit Table(const char* tbl_id, const TableOptions& options);
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
    TableOptions Options;

  private:
    ImVec2 m_outer_size;
    float m_inner_width;
  };
}

#endif //APUI_WIDGETS_TABLES_TABLE_HPP
