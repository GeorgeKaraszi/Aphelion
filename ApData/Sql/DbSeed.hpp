#ifndef APDATA_SQL_DBSEED_HPP
#define APDATA_SQL_DBSEED_HPP

#include <SQLiteCpp/SQLiteCpp.h>
#include <ApCore/Nets/CensusAPI.hpp>

namespace ApData::Sql::DBSeed
{
  void InitializeTables(SQLite::Database &db, ApCore::Nets::CensusAPI *census);
}
#endif //APDATA_SQL_DBSEED_HPP
