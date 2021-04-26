#ifndef APDATA_SQL_MODELS_ITEM_HPP
#define APDATA_SQL_MODELS_ITEM_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  namespace Data
  {
    struct alignas(128) Item
    {
      int id                 { -1 };
      int item_id            { -1 };
      int item_category_id   { -1 };
      int faction_id         { -1 };
      int is_vehicle_weapon  { false };
      std::string image_path;
      std::string name       { "[Unknown]" };
    };
  }
  class Item : public AModel<Data::Item, 7>
  {
    using AModel::AModel;
  public:
    Item(const Item&) = default;
    explicit Item(ApData::Sql::Database &database) : AModel(database, "items") {}

    Data::Item FindByItemID(int item_id)
    {
      auto results = FetchBy(fmt::format("item_id = {}", item_id));

      if(results.empty())
      {
        return Data::Item();
      }

      return results.front();
    }

  protected:
    std::string TableSchema() override {
      return R"(
         CREATE TABLE items(
            id                INTEGER PRIMARY KEY,
            item_id           INTEGER,
            item_category_id  INTEGER,
            faction_id        INTEGER,
            is_vehicle_weapon BOOLEAN,
            image_path        TEXT,
            name              TEXT
          );
          CREATE UNIQUE INDEX idx_item_id ON items(item_id);
          CREATE INDEX idx_items_category_id ON items(item_category_id);
          CREATE INDEX idx_item_cat_faction_ids ON items(item_id, item_category_id, faction_id);
         )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      return fmt::format(
          "INSERT INTO items(item_id, item_category_id, faction_id, is_vehicle_weapon, image_path, name) "\
          "VALUES ({}, {}, {}, {}, '{}', '{}')",
          Data.item_id,
          Data.item_category_id,
          Data.faction_id,
          Data.is_vehicle_weapon,
          Data.image_path,
          Data.name
      );
    }

    std::string ExistsConditional() override {
      std::string name = Data.name;
      boost::replace_all(name, "'", "''");
      return fmt::format("item_id = {} AND name = '{}'", Data.item_id, name);
    }

  public:
    Data::Item Data;
  };
}

#endif //APDATA_SQL_MODELS_ITEM_HPP
