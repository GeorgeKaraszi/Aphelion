#ifndef APDATA_SQL_MODELS_LOADOUT_HPP
#define APDATA_SQL_MODELS_LOADOUT_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  namespace Data
  {
    struct alignas(128) Loadout {
      int id         { -1 };
      int loadout_id { 0 };
      int profile_id { 0 };
      int faction_id { 0 };
      std::string name;
      std::string code_name;
    };
  }
  class Loadout : public AModel<Data::Loadout, 6>
  {
    using AModel::AModel;
  public:
    Loadout(const Loadout&) = default;
    explicit Loadout(ApData::Sql::Database &database) : AModel(database, "loadouts")
    {}

    std::vector<Data::Loadout> FetchByProfileID(int profile_id)
    {
      return FetchBy(fmt::format("profile_id = {}", profile_id));
    }

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
      return fmt::format(
          "INSERT INTO loadouts(loadout_id, profile_id, faction_id, name, code_name) VALUES ({}, {}, {}, '{}', '{}')",
          Data.loadout_id,
          Data.profile_id,
          Data.faction_id,
          Data.name,
          Data.code_name
      );
    }

    std::string ExistsConditional() override {
      auto name = Data.name;
      boost::replace_all(name, "'", "''");
      return fmt::format(
          "faction_id = {} AND profile_id = {} AND name = '{}'",
          Data.faction_id,
          Data.profile_id,
          name
      );
    }

  public:
    Data::Loadout Data;
  };
}

#endif //APDATA_SQL_MODELS_LOADOUT_HPP
