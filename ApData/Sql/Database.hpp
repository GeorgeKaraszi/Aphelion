#ifndef APDATA_SQL_DATABASE_HPP
#define APDATA_SQL_DATABASE_HPP

#include <SQLiteCpp/SQLiteCpp.h>

namespace ApData::Sql
{
  class Database : public SQLite::Database
  {
  public:
    explicit Database(
        const std::string & db_file_name = "ap_data.db",
        int db_flags = SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE
    );

    Database &Get();
    static Database* GetDatabase();
  };
}

#endif //APDATA_SQL_DATABASE_HPP
