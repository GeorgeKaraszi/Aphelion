#ifndef APDATA_SQL_MODELS_AMODEL_HPP
#define APDATA_SQL_MODELS_AMODEL_HPP

#include <ApInclude/string_helper.hpp>
#include <ApData/Sql/Database.hpp>

namespace ApData::Sql::Models
{
  class AModel
  {
  public:
    AModel()              = delete;
    AModel(const AModel&) = default;
    explicit AModel(SQLite::Database &database) : db(database)
    {};

    [[nodiscard]]
    virtual std::string TableName() const = 0;

    bool TableExists()
    {
      return db.tableExists(TableName());
    }

    int CreateTable()
    {
      if(TableExists())
      {
        return 0;
      }

      return db.exec(TableSchema());
    }

    int DropTable()
    {
      if(!db.tableExists(TableName()))
      {
        return 0;
      }

      auto drop_tbl = format_string("DROP TABLE %s", TableName().c_str());
      return db.exec(drop_tbl);
    }

    int CreateRecord()
    {
      if(Exists())
      {
        return 0;
      }

      std::string insert_query = RecordInsertQuery();
      return SQLite::Statement(db, insert_query).exec();
    }

    virtual bool Exists()
    {
      std::string query = format_string(
          "SELECT COUNT(*) FROM %s WHERE %s LIMIT 1",
          TableName().c_str(),
          ExistsConditional().c_str()
      );

      return db.execAndGet(query).getInt() > 0;
    }

  protected:
    virtual std::string TableSchema()       = 0;
    virtual std::string RecordInsertQuery() = 0;
    virtual std::string ExistsConditional() = 0;

  protected:
    SQLite::Database &db;
  };
}

#endif //APDATA_SQL_MODELS_AMODEL_HPP
