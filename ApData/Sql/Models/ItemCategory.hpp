#ifndef APDATA_SQL_MODELS_ITEMCATEGORY_HPP
#define APDATA_SQL_MODELS_ITEMCATEGORY_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  namespace Data
  {
    struct alignas(64) ItemCategory
    {
      int id               { -1 };
      int item_category_id { -1 };
      std::string name;
    };
  }
  class ItemCategory : public AModel<Data::ItemCategory, 3>
  {
    using AModel::AModel;
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
      return fmt::format(
          "INSERT INTO item_categories(item_category_id, name) VALUES ({}, '{}')",
          Data.item_category_id,
          Data.name
      );
    }

    std::string ExistsConditional() override {
      auto name = Data.name;
      boost::replace_all(name, "'", "''");
      return fmt::format("name = '{}'", name);
    }

  public:
    Data::ItemCategory Data;
  };
}
#endif //APDATA_SQL_MODELS_ITEMCATEGORY_HPP
