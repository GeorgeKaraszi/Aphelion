#ifndef APDATA_SQL_MODELS_PLAYER_HPP
#define APDATA_SQL_MODELS_PLAYER_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  class Player : public AModel
  {
    using AModel::AModel;

  public:
    struct TableData
    {
      int faction_id;
      std::string character_id;
      std::string name;
    };

  public:
    Player(const Player&) = default;
    explicit Player(ApData::Sql::Database &database) : AModel(database, "players")
    {}

  protected:
    std::string TableSchema() override {
      return  R"(
        CREATE TABLE players(
            id               INTEGER PRIMARY KEY,
            character_id     TEXT,
            faction_id       INTEGER,
            name             TEXT
        );
        CREATE UNIQUE INDEX idx_players_character_id ON players(character_id);
      )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      return format_string(
          "INSERT INTO players(character_id, name, faction_id) VALUES ('%s', '%s', %i)",
          Data.character_id.c_str(),
          Data.name.c_str(),
          Data.faction_id
      );
    }

    std::string ExistsConditional() override {
      return format_string("name = '%s' OR character_id = '%s", Data.name.c_str(), Data.character_id);
    }

  public:
    TableData Data;
  };
}
#endif //APDATA_SQL_MODELS_PLAYER_HPP
