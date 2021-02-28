#ifndef APDATA_SQL_DATABASE_HPP
#define APDATA_SQL_DATABASE_HPP

#include <ApInclude/pch.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

namespace ApData::Sql
{
  class Database
  {
  public:
    explicit Database(
        const std::string & db_file_name = "ap_data.db",
        int db_flags = SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE
    );

    SQLite::Database &Get();
    static Database* GetDatabase();

  private:
    SQLite::Database db;
  };
}

#endif //APDATA_SQL_DATABASE_HPP
