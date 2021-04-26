#ifndef APDATA_SQL_MODELS_PLAYER_HPP
#define APDATA_SQL_MODELS_PLAYER_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  namespace Data
  {
    struct alignas(128) Player
    {
      int id         { -1 };
      int faction_id { 0 };
      std::string character_id;
      std::string name;
    };
  }
  class Player : public AModel<Data::Player, 4>
  {
    using AModel::AModel;
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
      return fmt::format(
          "INSERT INTO players(character_id, name, faction_id) VALUES ('{}', '{}', {})",
          Data.character_id,
          Data.name,
          Data.faction_id
      );
    }

    std::string ExistsConditional() override {
      auto name = Data.name;
      boost::replace_all(name, "'", "''");
      return fmt::format("name = '{}' OR character_id = '{}", name, Data.character_id);
    }

  public:
    Data::Player Data;
  };
}
#endif //APDATA_SQL_MODELS_PLAYER_HPP
