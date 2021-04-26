#ifndef APDATA_SQL_MODELS_PROFILE_HPP
#define APDATA_SQL_MODELS_PROFILE_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  namespace Data
  {
    struct alignas(128) Profile {
      int id              { -1 };
      int profile_id      { -1 };
      int profile_type_id { -1 };
      int faction_id      { 0 };
      std::string name;
      std::string description;
      std::string image_path;
    };
  }
  class Profile : public AModel<Data::Profile, 7>
  {
    using AModel::AModel;
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
      return fmt::format(
          "INSERT INTO profiles(profile_id, profile_type_id, faction_id, name, description, image_path) "\
          "VALUES ({}, {}, {}, '{}', '{}', '{}')",
          Data.profile_id,
          Data.profile_type_id,
          Data.faction_id,
          Data.name,
          Data.description,
          Data.image_path
      );
    }

    std::string ExistsConditional() override {
      auto name = Data.name;
      boost::replace_all(name, "'", "''");
      return fmt::format(
          "faction_id = {} AND profile_id = {} AND profile_type_id = {} AND name = '{}'",
          Data.faction_id,
          Data.profile_id,
          Data.profile_type_id,
          name
      );
    }
  public:
    Data::Profile Data;
  };
}

#endif //APDATA_SQL_MODELS_PROFILE_HPP
