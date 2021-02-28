#ifndef APDATA_SQL_DBSEED_HPP
#define APDATA_SQL_DBSEED_HPP

#include "Database.hpp"
#include <ApCore/Nets/CensusAPI.hpp>

namespace ApData::Sql::DBSeed
{
  void InitializeTables(ApData::Sql::Database &db, ApCore::Nets::CensusAPI *census);
}
#endif //APDATA_SQL_DBSEED_HPP
