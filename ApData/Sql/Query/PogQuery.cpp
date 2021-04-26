#include "PogQuery.hpp"
#include <iostream>
#include <ApData/Sql/Models/Event.hpp>

namespace ApData::Sql::Query::PogQuery
{
 PogRules GetPogRules(ApData::Sql::Database &db)
 {
   using namespace ApData::Sql::Models::Data;
   PogRules rules;
   auto event_model = ApData::Sql::Models::Event(db);
   auto event_data  = event_model.FetchByType("POG");

   auto banned_item_cat_query = FMT_STRING(
       "SELECT DISTINCT items.item_id AS item_id "\
        "FROM items "\
        "INNER JOIN item_categories ON item_categories.item_category_id = items.item_category_id "\
        "WHERE item_categories.name = '{}'"
        );

   auto banned_item_query = FMT_STRING(
       "SELECT DISTINCT items.item_id AS item_id "\
        "FROM items "\
        "WHERE items.name LIKE '%{}%'"
        );

   auto banned_profile_query = FMT_STRING(
        "SELECT DISTINCT profiles.profile_id AS profile_id "\
        "FROM profiles "\
        "WHERE name = '{}' OR description = '{}'"
       );

   for(const auto &data : event_data)
   {
     switch(data.category_id)
     {
       case EventCategories::KILL:
         rules.kill = data.points;
         break;
       case EventCategories::DEATH:
         rules.death = data.points;
         break;
       case EventCategories::TEAM_KILL:
         rules.team_kill = data.points;
         break;
       case EventCategories::SUICIDE:
         rules.suicide = data.points;
         break;
       case EventCategories::MAX_KILL:
         rules.max_kill = data.points;
         break;
       case EventCategories::MAX_TEAM_KILL:
         rules.max_team_kill = data.points;
         break;
       case EventCategories::MAX_SUICIDE:
         rules.max_suicide = data.points;
         break;
       case EventCategories::BASE_CAPTURE:
         rules.base_capture = data.points;
         break;
       case EventCategories::BASE_RECAPTURE:
         rules.base_recapture = data.points;
         break;
       case EventCategories::BANNED_CLASS:
       {
         auto query = event_model.QueryBy(fmt::format(banned_profile_query, data.meta_data, data.meta_data));

         while(query.executeStep())
         {
           rules.banned_profile_ids.push_back(query.getColumn("profile_id").getInt());
         }

         break;
       }
       case EventCategories::BANNED_ITEM_CATEGORY:
       case EventCategories::BANNED_ITEM:
       {
         std::string query_str;
         auto meta_data = data.meta_data.c_str();
         if(data.category.ends_with("CATEGORY"))
         {
           query_str = fmt::format(banned_item_cat_query, meta_data);
         }
         else
         {
           query_str = fmt::format(banned_item_query, meta_data);
         }

         auto query = event_model.QueryBy(query_str);

         while(query.executeStep())
         {
           rules.banned_item_ids.push_back(query.getColumn("item_id").getInt());
         }
       }
       break;
       default:
         break;
     }
   }

   return rules;
 }
}