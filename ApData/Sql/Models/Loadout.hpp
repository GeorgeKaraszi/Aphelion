#ifndef APDATA_SQL_MODELS_LOADOUT_HPP
#define APDATA_SQL_MODELS_LOADOUT_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  class Loadout : public AModel
  {
    using AModel::AModel;
  public:
    struct TableData {
      int loadout_id;
      int profile_id;
      int faction_id;
      std::string name;
      std::string code_name;
    };

  public:
    Loadout(const Loadout&) = default;
    explicit Loadout(ApData::Sql::Database &database) : AModel(database, "loadouts")
    {}

  protected:
    std::string TableSchema() override {
      return R"(
         CREATE TABLE loadouts(
            id         INTEGER PRIMARY KEY,
            loadout_id INTEGER,
            profile_id INTEGER,
            faction_id INTEGER,
            name       TEXT,
            code_name  TEXT
          );
          CREATE INDEX idx_loadout_id ON loadouts(loadout_id);
          CREATE INDEX idx_loadout_faction_ids ON loadouts(loadout_id, faction_id);
      )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      return format_string(
          "INSERT INTO loadouts(loadout_id, profile_id, faction_id, name, code_name) VALUES (%i, %i, %i, '%s', '%s')",
          Data.loadout_id,
          Data.profile_id,
          Data.faction_id,
          Data.name.c_str(),
          Data.code_name.c_str()
      );
    }

    std::string ExistsConditional() override {
      auto name = Data.name;
      boost::replace_all(name, "'", "''");
      return format_string(
          "faction_id = %i AND profile_id = %i AND name = '%s'",
          Data.faction_id,
          Data.profile_id,
          name.c_str()
      );
    }
  public:
    TableData Data;
  };
}

#endif //APDATA_SQL_MODELS_LOADOUT_HPP
