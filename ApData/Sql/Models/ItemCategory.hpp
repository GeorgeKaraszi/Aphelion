#ifndef APDATA_SQL_MODELS_ITEMCATEGORY_HPP
#define APDATA_SQL_MODELS_ITEMCATEGORY_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  class ItemCategory : public AModel
  {
    using AModel::AModel;

  public:
    struct TableData
    {
      int id;
      int item_category_id;
      std::string name;
    };

  public:
    ItemCategory(const ItemCategory&) = default;
    explicit ItemCategory(ApData::Sql::Database &database) : AModel(database, "item_categories")
    {}

  protected:
    std::string TableSchema() override {
      return  R"(
        CREATE TABLE item_categories(
            id               INTEGER PRIMARY KEY,
            item_category_id INTEGER,
            name             TEXT
        );
        CREATE UNIQUE INDEX idx_item_category_id ON item_categories(item_category_id);
      )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      return format_string(
          "INSERT INTO item_categories(item_category_id, name) VALUES (%i, '%s')",
          Data.item_category_id,
          Data.name.c_str()
      );
    }

    std::string ExistsConditional() override {
      auto name = Data.name;
      boost::replace_all(name, "'", "''");
      return format_string("name = '%s'", name.c_str());
    }

  public:
    TableData Data;
  };
}
#endif //APDATA_SQL_MODELS_ITEMCATEGORY_HPP
