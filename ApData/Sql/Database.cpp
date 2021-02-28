#include "Database.hpp"

static ApData::Sql::Database* g_database = nullptr;

namespace ApData::Sql
{
  Database::Database(const std::string &db_file_name, int db_flags) : SQLite::Database(db_file_name, db_flags)
  {
    g_database = this;
  }

  Database &Database::Get()
  {
    return std::ref(*this);
  }

  Database* Database::GetDatabase()
  {
    return g_database;
  }
}