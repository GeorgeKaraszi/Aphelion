#ifndef APDATA_SQL_MODELS_OUTFIT_HPP
#define APDATA_SQL_MODELS_OUTFIT_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  class Outfit : public AModel
  {
    using AModel::AModel;

  public:
    struct TableData
    {
      int faction_id;
      std::string outfit_id;
      std::string name;
      std::string tag;
    };

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
      return format_string(
          "INSERT INTO outfits(faction_id, outfit_id, name, tag) VALUES (%i, '%s', '%s', '%s')",
          Data.faction_id,
          Data.outfit_id.c_str(),
          Data.name.c_str(),
          Data.tag.c_str()
      );
    }

    std::string ExistsConditional() override {
      return format_string("outfit_id = '%s'", Data.outfit_id.c_str());
    }

  public:
    TableData Data;
  };
}
#endif //APDATA_SQL_MODELS_OUTFIT_HPP
