#ifndef APDATA_SQL_DBSEED_HPP
#define APDATA_SQL_DBSEED_HPP

#include "Database.hpp"
#include <ApCore/Nets/CensusAPI.hpp>

namespace ApData::Sql::DBSeed
{
  using ReporterCallback = std::function<void(std::string, bool error)>;

  void InitializeTables(
      ApData::Sql::Database& db,
      const std::shared_ptr<ApCore::Nets::CensusAPI>& census
  );

  void InitializeTables(
      ApData::Sql::Database& db,
      const std::shared_ptr<ApCore::Nets::CensusAPI>& census,
      const ReporterCallback &reporter
  );
}
#endif //APDATA_SQL_DBSEED_HPP
