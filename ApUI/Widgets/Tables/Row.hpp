#ifndef APUI_WIDGETS_TABLES_ROW_HPP
#define APUI_WIDGETS_TABLES_ROW_HPP

#include <ApUI/Widgets/Layout/Group.hpp>
#include <ApUI/Widgets/Texts/TextColored.hpp>
#include <map>

namespace ApUI::Widgets::Tables
{
  class Table;
  class Row : public Layout::Group
  {
  public:
    explicit Row(std::string row_id, Table* table);
    Texts::TextColored &operator[](const std::string& key);
    Texts::TextColored &FindOrCreateColumnData(const std::string &key);
  protected:
    void _Draw_Impl() override;

  public:
    const std::string RowID;

  private:
    Table *m_table;
    std::map<std::string, Texts::TextColored*> m_data;

  };
}

#endif //APUI_WIDGETS_TABLES_ROW_HPP
