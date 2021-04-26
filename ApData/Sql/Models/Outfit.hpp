#ifndef APDATA_SQL_MODELS_OUTFIT_HPP
#define APDATA_SQL_MODELS_OUTFIT_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  namespace Data
  {
    struct alignas(128) Outfit
    {
      int id         { -1 };
      int faction_id { -1 };
      std::string outfit_id;
      std::string name;
      std::string tag;
    };
  }

  class Outfit : public AModel<Data::Outfit, 5>
  {
    using AModel::AModel;
  public:
    Outfit(const Outfit&) = default;
    explicit Outfit(ApData::Sql::Database &database) : AModel(database, "outfits")
    {}

  protected:
    std::string TableSchema() override {
      return  R"(
        CREATE TABLE outfits(
            id               INTEGER PRIMARY KEY,
            faction_id       INTEGER,
            outfit_id        TEXT,
            name             TEXT,
            tag              TEXT
        );
        CREATE UNIQUE INDEX idx_outfits_outfit_id ON outfits(outfit_id);
        CREATE INDEX idx_outfits_tag ON outfits(tag);
      )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      return fmt::format(
          "INSERT INTO outfits(faction_id, outfit_id, name, tag) VALUES ({}, '{}', '{}', '{}')",
          Data.faction_id,
          Data.outfit_id,
          Data.name,
          Data.tag
      );
    }

    std::string ExistsConditional() override {
      return fmt::format("outfit_id = '{}'", Data.outfit_id);
    }

  public:
    Data::Outfit Data;
  };
}
#endif //APDATA_SQL_MODELS_OUTFIT_HPP
