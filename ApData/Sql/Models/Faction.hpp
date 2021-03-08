#ifndef APDATA_SQL_MODELS_FACTION_HPP
#define APDATA_SQL_MODELS_FACTION_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  class Faction : public AModel
  {
    using AModel::AModel;

  public:
    struct TableData
    {
      int faction_id;
      bool user_selectable;
      std::string name;
      std::string code_tag;
      std::string image_set_id;
      std::string image_path;
    };

  public:
    Faction(const Faction&) = default;
    explicit Faction(ApData::Sql::Database &database) : AModel(database, "factions")
    {}

  protected:
    std::string TableSchema() override {
      return  R"(
        CREATE TABLE factions(
            id               INTEGER PRIMARY KEY,
            faction_id       INTEGER,
            user_selectable  BOOLEAN,
            name             TEXT,
            code_tag         TEXT,
            image_set_id     TEXT,
            image_path       TEXT
        );
        CREATE INDEX idx_factions_faction_id ON factions(faction_id);
        CREATE INDEX idx_factions_code_tag   ON factions(code_tag);
      )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      boost::replace_all(Data.code_tag, "'", "''");
      return format_string(
          "INSERT INTO factions(faction_id, user_selectable, name, code_tag, image_set_id, image_path) "\
          "VALUES (%i, %i, '%s', '%s', '%s', '%s')",
          Data.faction_id,
          Data.user_selectable,
          Data.name.c_str(),
          Data.code_tag.c_str(),
          Data.image_set_id.c_str(),
          Data.image_path.c_str()
      );
    }

    std::string ExistsConditional() override {
      auto name     = Data.name;
      auto code_tag = Data.code_tag;
      boost::replace_all(name, "'", "''");
      boost::replace_all(code_tag, "'", "''");
      return format_string("name = '%s' AND code_tag = '%s'", name.c_str(), code_tag.c_str());
    }

  public:
    TableData Data;
  };
}
#endif //APDATA_SQL_MODELS_ITEMCATEGORY_HPP
