#ifndef APDATA_SQL_MODELS_VEHICLE_HPP
#define APDATA_SQL_MODELS_VEHICLE_HPP

#include "AModel.hpp"

namespace ApData::Sql::Models
{
  namespace Data
  {
    struct alignas(128) Vehicle {
      int id              { -1 };
      int vehicle_id      { -1 };
      int type_id         { -1 };
      std::string name;
      std::string image_set_id;
      std::string image_path;
    };
  }
  class Vehicle : public AModel<Data::Vehicle, 6>
  {
    using AModel::AModel;
  public:
    Vehicle(const Vehicle&) = default;
    explicit Vehicle(ApData::Sql::Database &database) : AModel(database, "vehicles")
    {}

  protected:
    std::string TableSchema() override {
      return R"(
         CREATE TABLE vehicles(
            id              INTEGER PRIMARY KEY,
            vehicle_id      INTEGER,
            type_id         INTEGER,
            name            TEXT,
            image_set_id    TEXT,
            image_path      TEXT
          );
          CREATE INDEX idx_vehicles_vehicle_id ON vehicles(vehicle_id);
          CREATE UNIQUE INDEX idx_vehicles_vehicle_n_type_ids ON vehicles(vehicle_id, type_id);
      )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.name, "'", "''");
      return fmt::format(
          "INSERT INTO vehicles(vehicle_id, type_id, name, image_set_id, image_path) "\
          "VALUES ({}, {}, '{}', '{}', '{}')",
          Data.vehicle_id,
          Data.type_id,
          Data.name,
          Data.image_set_id,
          Data.image_path
       );
    }

    std::string ExistsConditional() override {
      auto name = Data.name;
      boost::replace_all(name, "'", "''");
      return fmt::format("name = '{}' AND type_id = {}", name, Data.type_id);
    }
  public:
    Data::Vehicle Data;
  };
}

#endif //APDATA_SQL_MODELS_VEHICLE_HPP
