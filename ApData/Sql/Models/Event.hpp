#ifndef APDATA_SQL_MODELS_EVENT_HPP
#define APDATA_SQL_MODELS_EVENT_HPP
#include "AModel.hpp"

namespace ApData::Sql::Models
{
  namespace Data
  {
    enum EventCategories
    {
      DEFAULT              = 0,
      KILL                 = 1,
      DEATH                = 2,
      TEAM_KILL            = 3,
      SUICIDE              = 4,
      MAX_KILL             = 5,
      MAX_TEAM_KILL        = 6,
      MAX_SUICIDE          = 7,
      BASE_CAPTURE         = 8,
      BASE_RECAPTURE       = 9,
      BANNED_CLASS         = 10,
      BANNED_ITEM_CATEGORY = 11,
      BANNED_ITEM          = 12
    };
    struct alignas(128) Event
    {
      int id          { -1 };
      int points      { 0 };
      int category_id { EventCategories::DEFAULT };
      std::string category;
      std::string type;
      std::string meta_data;
    };
  }
  class Event : public AModel<Data::Event, 6>
  {
    using AModel::AModel;
  public:
    Event(const Event&) = default;
    explicit Event(ApData::Sql::Database &database) : AModel(database, "events")
    {}

    std::vector<Data::Event> FetchByType(const char* type)
    {
      return FetchBy(fmt::format("type = '{}'", type));
    }

  protected:
    std::string TableSchema() override {
      return  R"(
        CREATE TABLE events(
            id               INTEGER PRIMARY KEY,
            points           INTEGER,
            category_id      INTEGER,
            category         TEXT,
            type             TEXT,
            meta_data        TEXT
        );
        CREATE INDEX events_type          ON events(type);
        CREATE INDEX idx_type_category    ON events(type,category);
        CREATE INDEX idx_type_category_id ON events(type, category_id)
      )";
    }

    std::string RecordInsertQuery() override {
      boost::replace_all(Data.type, "'", "''");
      boost::replace_all(Data.category, "'", "''");
      boost::replace_all(Data.meta_data, "'", "''");
      return fmt::format(
          "INSERT INTO events(points, category_id, category, type, meta_data) "\
          "VALUES ({}, {}, '{}', '{}', '{}')",
          Data.points,
          Data.category_id,
          Data.category,
          Data.type,
          Data.meta_data
      );
    }

    std::string ExistsConditional() override {
      auto type      = Data.type;
      auto meta_data = Data.meta_data;
      boost::replace_all(type, "'", "''");
      boost::replace_all(meta_data, "'", "''");
      return fmt::format("type = '{}' AND meta_data = '{}' AND category_id = {}", type, meta_data, Data.category_id);
    }

  public:
    Data::Event Data;
  };
}
#endif //APDATA_SQL_MODELS_EVENT_HPP
