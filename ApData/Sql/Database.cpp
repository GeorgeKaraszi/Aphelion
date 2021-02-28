#include "Database.hpp"

static ApData::Sql::Database* g_database = nullptr;

namespace ApData::Sql
{
  Database::Database(const std::string &db_file_name, int db_flags) : db(db_file_name, db_flags)
  {
    g_database = this;
  }

  SQLite::Database &Database::Get()
  {
    return db;
  }

  Database* Database::GetDatabase()
  {
    return g_database;
  }
}