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
    [[nodiscard]]
    std::string TableName() const override { return "item_categories"; }

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
      return format_string(
          "INSERT INTO item_categories(item_category_id, name) VALUES (%i, '%s')",
          Data.item_category_id,
          Data.name.c_str()
      );
    }

    std::string ExistsConditional() override {
      return format_string("name = '%s'", Data.name.c_str());
    }

  public:
    TableData Data;
  };
}
#endif //APDATA_SQL_MODELS_ITEMCATEGORY_HPP
