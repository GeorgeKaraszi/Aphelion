#ifndef APDATA_SQL_MODELS_PROFILE_HPP
#define APDATA_SQL_MODELS_PROFILE_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  class Profile : public AModel
  {
    using AModel::AModel;
  public:
    struct TableData {
      int profile_id;
      int profile_type_id;
      int faction_id;
      std::string name;
      std::string description;
      std::string image_path;
    };

  public:
    Profile(const Profile&) = default;
    explicit Profile(ApData::Sql::Database &database) : AModel(database, "profiles")
    {}

  protected:
    std::string TableSchema() override {
      return R"(
         CREATE TABLE profiles(
            id              INTEGER PRIMARY KEY,
            profile_id      INTEGER,
            profile_type_id INTEGER,
            faction_id      INTEGER,
            name            TEXT,
            description     TEXT,
            image_path      TEXT
          );
          CREATE INDEX idx_profile_id ON profiles(profile_id);
          CREATE INDEX idx_profile_faction_ids ON profiles(profile_id, faction_id);
      )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      boost::replace_all(Data.description, "'", "''");
      return format_string(
          "INSERT INTO profiles(profile_id, profile_type_id, faction_id, name, description, image_path) "\
          "VALUES (%i, %i, %i, '%s', '%s', '%s')",
          Data.profile_id,
          Data.profile_type_id,
          Data.faction_id,
          Data.name.c_str(),
          Data.description.c_str(),
          Data.image_path.c_str()
      );
    }

    std::string ExistsConditional() override {
      auto name = Data.name;
      boost::replace_all(name, "'", "''");
      return format_string(
          "faction_id = %i AND profile_id = %i AND profile_type_id = %i AND name = '%s'",
          Data.faction_id,
          Data.profile_id,
          Data.profile_type_id,
          name.c_str()
      );
    }
  public:
    TableData Data;
  };
}

#endif //APDATA_SQL_MODELS_PROFILE_HPP
