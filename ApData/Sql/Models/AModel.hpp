#ifndef APDATA_SQL_MODELS_AMODEL_HPP
#define APDATA_SQL_MODELS_AMODEL_HPP

#include <fmt/format.h>
#include <ApInclude/boost.hpp>
#include <ApData/Sql/Database.hpp>
#include <utility>

namespace ApData::Sql::Models
{
  template <typename T, const int column_count>
  class AModel
  {
  public:
    AModel()              = delete;
    AModel(const AModel&) = default;
    explicit AModel(ApData::Sql::Database &database, std::string tbl_name)
    : db(database), TableName(std::move(tbl_name))
    {};

    bool TableExists()
    {
      return db.tableExists(TableName);
    }

    bool CreateTable()
    {
      if(TableExists())
      {
        return false;
      }

      db.exec(TableSchema());
      return db.getErrorCode() == EXIT_SUCCESS;
    }

    int Count()
    {
      if(!TableExists())
      {
        return 0;
      }

      auto count_records = fmt::format("SELECT COUNT(*) FROM {}", TableName);
      return db.execAndGet(count_records).getInt();
    }

    int DropTable()
    {
      if(!TableExists())
      {
        return 0;
      }

      auto drop_tbl = fmt::format("DROP TABLE {}", TableName);
      return db.exec(drop_tbl);
    }

    int TruncateTable()
    {
      if(TableExists())
      {
        db.exec(fmt::format("DELETE FROM {}", TableName));
        return db.getErrorCode() == EXIT_SUCCESS;
      }

      return EXIT_FAILURE;
    }

    int CreateRecord()
    {
      if(Exists())
      {
        return EXIT_FAILURE;
      }

      return QueryBy(RecordInsertQuery()).exec();
    }

    virtual bool Exists()
    {
      auto conditional  = ExistsConditional();
      std::string query = fmt::format("SELECT COUNT(*) FROM {} WHERE {} LIMIT 1", TableName, ExistsConditional());

      return db.execAndGet(query).getInt() > 0;
    }

    std::vector<T> FetchBy(const std::string &where_clause)
    {
      std::vector<T> data;
      SQLite::Statement query(QueryBy(fmt::format("SELECT * FROM {} WHERE {}", TableName, where_clause)));

      while(query.executeStep())
      {
        auto tbl_data = query.getColumns<T, column_count>();
        data.push_back(tbl_data);
      }

      return data;
    }

//    template<typename O, int N>
//    std::vector<O> FetchBy(const std::string &query_stm)
//    {
//      std::vector<T> data;
//      SQLite::Statement query(QueryBy(query_stm));
//
//      while(query.executeStep())
//      {
//        T tbl_data = query.template getColumns<O, N>();
//        data.push_back(tbl_data);
//      }
//
//      return data;
//    }

    virtual inline SQLite::Statement QueryBy(const std::string &query)
    {
      return SQLite::Statement(db, query);
    }

  protected:
    virtual std::string TableSchema()       = 0;
    virtual std::string RecordInsertQuery() = 0;
    virtual std::string ExistsConditional() = 0;

  public:
    const std::string TableName;

  protected:
    ApData::Sql::Database &db;
  };
}

#endif //APDATA_SQL_MODELS_AMODEL_HPP
