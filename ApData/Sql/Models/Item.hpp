#ifndef APDATA_SQL_MODELS_ITEM_HPP
#define APDATA_SQL_MODELS_ITEM_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  class Item : public AModel
  {
  public:
    struct TableData
    {
      int item_id = -1;
      int item_category_id = -1;
      int faction_id = -1;
      bool is_vehicle_weapon = false;
      std::string image_path;
      std::string name;
    };

  public:
    Item(const Item&) = default;
    explicit Item(ApData::Sql::Database &database) : AModel(database, "items") {}

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
          CREATE INDEX idx_item_cat_faction_ids ON items(item_id, item_category_id, faction_id);
         )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      return format_string(
          "INSERT INTO items(item_id, item_category_id, faction_id, is_vehicle_weapon, image_path, name) "\
          "VALUES (%i, %i, %i, %i, '%s', '%s')",
          Data.item_id,
          Data.item_category_id,
          Data.faction_id,
          Data.is_vehicle_weapon,
          Data.image_path.c_str(),
          Data.name.c_str()
      );
    }

    std::string ExistsConditional() override {
      std::string name = Data.name;
      boost::replace_all(name, "'", "''");
      return format_string("item_id = %i AND name = '%s'", Data.item_id, name.c_str());
    }

  public:
    TableData Data;
  };
}

#endif //APDATA_SQL_MODELS_ITEM_HPP
