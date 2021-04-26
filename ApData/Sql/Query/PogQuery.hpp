#ifndef APDATA_SQL_QUERY_POGQUERY_HPP
#define APDATA_SQL_QUERY_POGQUERY_HPP

#include <ApData/Sql/Database.hpp>
#include <vector>

namespace ApData::Sql::Query::PogQuery
{
  struct alignas(128) PogRules
  {
    int kill;
    int death;
    int team_kill;
    int suicide;
    int max_kill;
    int max_suicide;
    int max_team_kill;
    int base_capture;
    int base_recapture;
    std::vector<int> banned_profile_ids;
    std::vector<int> banned_item_ids;
  };

  PogRules GetPogRules(ApData::Sql::Database &db);
}

#endif //APDATA_SQL_QUERY_POGQUERY_HPP
