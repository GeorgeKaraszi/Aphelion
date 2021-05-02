#ifndef APDATA_SQL_DBSEED_HPP
#define APDATA_SQL_DBSEED_HPP

#include "Database.hpp"
#include "Models/Loadout.hpp"
#include "Models/ItemCategory.hpp"
#include "Models/Item.hpp"
#include "Models/Profile.hpp"
#include "Models/Faction.hpp"
#include "Models/Event.hpp"
#include "Models/Vehicle.hpp"
#include <ApCore/Nets/CensusAPI.hpp>

namespace ApData::Sql
{
  class DBSeed
  {
  public:
    using ReporterCallback = std::function<void(std::string, bool error)>;

  public:
    DBSeed() = delete;
    [[maybe_unused]] explicit DBSeed(ApData::Sql::Database &database, ApCore::Nets::CensusAPI *census_api);
    explicit DBSeed(
        ApData::Sql::Database &database,
        ApCore::Nets::CensusAPI *census_api,
        ReporterCallback reporter
    );

    bool InitializeTables();

  private:
    bool VerifyCensusResponse(const char* what, const ApCore::Nets::CensusAPI::RESPONSE& response);

    u_long SeedItems(ApData::Sql::Models::Item&);
    int SeedFactions(ApData::Sql::Models::Faction&);
    int SeedProfiles(ApData::Sql::Models::Profile&);
    int SeedLoadouts(ApData::Sql::Models::Loadout&);
    int SeedVehicles(ApData::Sql::Models::Vehicle&);
    int SeedCategories(ApData::Sql::Models::ItemCategory&);
    int SeedEvents(ApData::Sql::Models::Event&);

  protected:
    bool fatal_error { false };

  private:
    ApData::Sql::Database &db;
    ApCore::Nets::CensusAPI *census;
    ReporterCallback reporter;
  };
}
#endif //APDATA_SQL_DBSEED_HPP
