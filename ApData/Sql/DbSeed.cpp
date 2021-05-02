#include <iostream>
#include <utility>
#include <ApInclude/fast_atio.hpp>
#include "DbSeed.hpp"
#include "Models/Player.hpp"
#include "Models/Outfit.hpp"

namespace ApData::Sql
{
  [[maybe_unused]]
  DBSeed::DBSeed(ApData::Sql::Database &database, ApCore::Nets::CensusAPI *census_api)
    : DBSeed(database, census_api, [](const std::string& msg, bool error) { fmt::print(msg); })
  {}

  DBSeed::DBSeed(
      ApData::Sql::Database &database,
      ApCore::Nets::CensusAPI *census_api,
      ReporterCallback reporter
  ) : db(database), census(census_api), reporter(std::move(reporter))
  {}

  bool DBSeed::InitializeTables()
  {
    unsigned long total_records_created = 0;
    ApData::Sql::Models::Item         items_model(db);
    ApData::Sql::Models::ItemCategory category_model(db);
    ApData::Sql::Models::Loadout      loadout_model(db);
    ApData::Sql::Models::Vehicle      vehicle_model(db);
    ApData::Sql::Models::Profile      profile_model(db);
    ApData::Sql::Models::Faction      faction_model(db);
    ApData::Sql::Models::Event        event_model(db);
    ApData::Sql::Models::Player(db).CreateTable();
    ApData::Sql::Models::Outfit(db).CreateTable();


    if(items_model.CreateTable())
    {
      reporter("Seeding Item's DB: This might take a while!", false);
      auto rec_count = SeedItems(items_model);
      total_records_created += rec_count;
      reporter(fmt::format("- Created {} Item Category Records", rec_count), false);
    }

    if(faction_model.CreateTable())
    {
      reporter("Seeding Faction DB:", false);
      auto rec_count = SeedFactions(faction_model);
      total_records_created += rec_count;
      reporter(fmt::format("- Created {} Faction Records", rec_count), false);
    }

    if(profile_model.CreateTable())
    {
      reporter("Seeding Profile DB:", false);
      auto rec_count = SeedProfiles(profile_model);
      total_records_created += rec_count;
      reporter(fmt::format("- Created {} Profile Records", rec_count), false);
    }

    if(loadout_model.CreateTable())
    {
      reporter("Seeding Loadout DB:", false);
      auto rec_count = SeedLoadouts(loadout_model);
      total_records_created += rec_count;
      reporter(fmt::format("- Created {} Loadout Records", rec_count), false);
    }

    if(vehicle_model.CreateTable())
    {
      reporter("Seeding Vehicle DB:", false);
      auto rec_count = SeedVehicles(vehicle_model);
      total_records_created += rec_count;
      reporter(fmt::format("- Created {} Vehicle Records", rec_count), false);
    }

    if(category_model.CreateTable())
    {
      reporter("Seeding Item Category DB:", false);
      auto rec_count = SeedCategories(category_model);
      total_records_created += rec_count;
      reporter(fmt::format("- Created {} Item Category Records", rec_count), false);
    }

    if(event_model.CreateTable())
    {
      reporter("Seeding Events DB:", false);
      auto rec_count = SeedEvents(event_model);
      total_records_created += rec_count;
      reporter(fmt::format("- Created {} Event Records", rec_count), false);
    }

    reporter(fmt::format("Created {} New Records in the DB", total_records_created), false);

    return !fatal_error;
  }

  bool DBSeed::VerifyCensusResponse(const char *what, const ApCore::Nets::CensusAPI::RESPONSE &response)
  {
    if(!response.success)
    {
      fatal_error = true;
      reporter(fmt::format("Error {}: {}", what, response.error), true);
      reporter(response.backtrace, true);
    }

    return response.success;
  }

  u_long DBSeed::SeedItems(ApData::Sql::Models::Item &model)
  {
    int returned;
    unsigned long created_record_count = 0;
    unsigned long next_set             = 0;
    auto census_template = FMT_STRING(
        "?c:join=weapon"\
        "&c:show=item_id,name.en,is_vehicle_weapon,item_category_id,faction_id,image_path"\
        "&c:has=item_category_id"\
        "&c:limit=5000"\
        "&c:start={}"
    );

    do {
      std::string census_query = fmt::format(census_template, next_set);
      auto response            = census->GetCensusQuery("/get/ps2:v2/item", census_query);

      if(!VerifyCensusResponse("SeedItems", response))
      {
        return created_record_count;
      }

      JSON item_data           = response.data;
      returned                 = item_data.contains("returned") ? item_data["returned"].get<int>() : 0;
      next_set                += returned;

      if(!item_data.contains("item_list") || !item_data["item_list"].is_array())
      {
        reporter(fmt::format("Error couldn't resolve Item Data!: {}", item_data.dump()), true);
        break;
      }

      for(auto item : item_data["item_list"])
      {
       try
       {
         model.Data.item_id           = fast_atoi(item["item_id"].get<std::string>());
         model.Data.item_category_id  = fast_atoi(item["item_category_id"].get<std::string>());
         model.Data.is_vehicle_weapon = item["is_vehicle_weapon"].get<std::string>() != "0";

         if(item.contains("faction_id") && item["faction_id"].is_string())
         {
           model.Data.faction_id = fast_atoi(item["faction_id"].get<std::string>());
         }
         else
         {
           model.Data.faction_id = 0;
         }

         item["image_path"].get_to(model.Data.image_path);
         item["name"]["en"].get_to(model.Data.name);
       }
       catch(...)
       {
         continue;
       }

        created_record_count += model.CreateRecord();
      }
    } while(returned == 5000);

    return created_record_count;
  }

  int DBSeed::SeedFactions(ApData::Sql::Models::Faction &model)
  {
    JSON faction_data;
    int created_record_count = 0;
    auto response            = census->GetCensusQuery("/get/ps2:v2/faction", "?c:limit=5000");

    if(!response.success)
    {
      reporter(fmt::format("Error Seeding Factions: {}", response.error), true);
      reporter(response.backtrace, true);
      return created_record_count;
    }

    faction_data = response.data;

    if(!faction_data.contains("faction_list") || !faction_data["faction_list"].is_array())
    {
      reporter(fmt::format("Error couldn't resolve Census Faction data!: {}", faction_data.dump()), true);
      return created_record_count;
    }

    for(const auto& faction : faction_data["faction_list"])
    {
      try
      {
        model.Data.image_set_id.clear();
        model.Data.image_path.clear();
        model.Data.faction_id      = fast_atoi(faction["faction_id"].get<std::string>());
        model.Data.user_selectable = faction["user_selectable"].get<std::string>() != "0";

        faction["code_tag"].get_to(model.Data.code_tag);
        faction["name"]["en"].get_to(model.Data.name);

        if(faction.contains("image_set_id"))
        {
          faction["image_set_id"].get_to(model.Data.image_set_id);
        }

        if(faction.contains("image_path"))
        {
          faction["image_path"].get_to(model.Data.image_path);
        }
      }
      catch(...)
      {
        continue;
      }

      created_record_count += model.CreateRecord();
    }

    return created_record_count;

  }

  int DBSeed::SeedProfiles(ApData::Sql::Models::Profile &model)
  {
    int created_record_count = 0;
    auto response = census->GetCensusQuery(
        "/get/ps2:v2/profile",
        "?c:show=profile_id,profile_type_id,profile_type_description,faction_id,name.en,image_path&c:limit=5000"
                                          );

    if(!VerifyCensusResponse("SeedProfiles", response))
    {
      return created_record_count;
    }

    JSON profile_data = response.data;

    if(!profile_data.contains("profile_list") || !profile_data["profile_list"].is_array())
    {
      reporter(fmt::format("Error couldn't resolve Census Profile data!: {}", profile_data.dump()), true);
      return 0;
    }

    for(const auto& profile : profile_data["profile_list"])
    {
      try
      {
        model.Data.profile_id      = fast_atoi(profile["profile_id"].get<std::string>());
        model.Data.profile_type_id = fast_atoi(profile["profile_type_id"].get<std::string>());
        model.Data.faction_id      = fast_atoi(profile["faction_id"].get<std::string>());

        profile["name"]["en"].get_to(model.Data.name);
        profile["image_path"].get_to(model.Data.image_path);
        profile["profile_type_description"].get_to(model.Data.description);
      }
      catch(...)
      {
        continue;
      }

      created_record_count += model.CreateRecord();
    }

    return created_record_count;
  }

  int DBSeed::SeedLoadouts(ApData::Sql::Models::Loadout &model)
  {
    int created_record_count = 0;
    auto response = census->GetCensusQuery("/get/ps2:v2/loadout", "?c:limit=5000");

    if(!VerifyCensusResponse("SeedLoadouts", response))
    {
      return created_record_count;
    }

    JSON loadout_data = response.data;
    std::vector<std::string> normalized_names = {
        "Light Assault",
        "Heavy Assault",
        "Medic",
        "Engineer",
        "Infiltrator",
        "MAX"
    };

    if(!loadout_data.contains("loadout_list") || !loadout_data["loadout_list"].is_array())
    {
      reporter(fmt::format("Error couldn't resolve Census Loadout data!: {}", loadout_data.dump()), true);
      return 0;
    }

    for(const auto& loadout : loadout_data["loadout_list"])
    {
      try
      {
        model.Data.profile_id = fast_atoi(loadout["profile_id"].get<std::string>());
        model.Data.faction_id = fast_atoi(loadout["faction_id"].get<std::string>());
        model.Data.loadout_id = fast_atoi(loadout["loadout_id"].get<std::string>());
        loadout["code_name"].get_to(model.Data.code_name);
        model.Data.name = "Unknown";

        for(const auto& name : normalized_names)
        {
          if(model.Data.code_name.find(name) != std::string::npos)
          {
            model.Data.name = name;
            break;
          }
        }

      }
      catch(...)
      {
        continue;
      }

      created_record_count += model.CreateRecord();
    }

    return created_record_count;
  }

  int DBSeed::SeedVehicles(ApData::Sql::Models::Vehicle &model)
  {
    int created_record_count = 0;
    auto response = census->GetCensusQuery("/get/ps2:v2/vehicle", "?c:show=vehicle_id,name.en,type_id,image_set_id,image_path&c:limit=500");

    if(!VerifyCensusResponse("SeedVehicles", response))
    {
      return created_record_count;
    }

    JSON vehicle_data = response.data;
    if(!vehicle_data.contains("vehicle_list") || !vehicle_data["vehicle_list"].is_array())
    {
      reporter(fmt::format("Error couldn't resolve Vehicle data!: {}", vehicle_data.dump()), true);
      return 0;
    }

    for(const auto &vehicle_item : vehicle_data["vehicle_list"])
    {
      try
      {
        ApData::Sql::Models::Data::Vehicle vec_data;
        vehicle_item["name"]["en"].get_to(model.Data.name);
        model.Data.image_path   = vehicle_item.contains("image_path") ? vehicle_item["image_path"].get<std::string>() : "";
        model.Data.image_set_id = vehicle_item.contains("image_set_id") ? vehicle_item["image_set_id"].get<std::string>() : "";
        model.Data.vehicle_id   = fast_atoi(vehicle_item["vehicle_id"].get<std::string>());
        model.Data.type_id      = fast_atoi(vehicle_item["type_id"].get<std::string>());
        created_record_count   += model.CreateRecord();
      }
      catch(...)
      {
        continue;
      }
    }

    return created_record_count;
  }

  int DBSeed::SeedCategories(ApData::Sql::Models::ItemCategory &model)
  {
    int created_record_count = 0;
    auto response = census->GetCensusQuery("/get/ps2:v2/item_category", "?c:show=item_category_id,name.en&c:limit=5000");

    if(!VerifyCensusResponse("SeedCategories", response))
    {
      return created_record_count;
    }

    JSON category_data = response.data;

    if(!category_data.contains("item_category_list") || !category_data["item_category_list"].is_array())
    {
      reporter(fmt::format("Error couldn't resolve Item Category data!: {}", category_data.dump()), true);
      return 0;
    }

    for(const auto &item_category : category_data["item_category_list"])
    {
      try
      {
        model.Data.item_category_id = fast_atoi(item_category["item_category_id"].get<std::string>());
        item_category["name"]["en"].get_to(model.Data.name);
      }
      catch(...)
      {
        continue;
      }

      created_record_count += model.CreateRecord();
    }

    return created_record_count;
  }

  int DBSeed::SeedEvents(ApData::Sql::Models::Event &model)
  {
    using namespace ApData::Sql::Models::Data;
    int created_record_count = 0;

    std::vector<ApData::Sql::Models::Data::Event> event_data = {
        { .points =  1, .category_id = EventCategories::KILL,                 .category = "KILL",                 .type = "POG", .meta_data = ""             },
        { .points = -1, .category_id = EventCategories::DEATH,                .category = "DEATH",                .type = "POG", .meta_data = ""             },
        { .points = -2, .category_id = EventCategories::TEAM_KILL,            .category = "TEAM_KILL",            .type = "POG", .meta_data = ""             },
        { .points = -1, .category_id = EventCategories::SUICIDE,              .category = "SUICIDE",              .type = "POG", .meta_data = ""             },
        { .points =  6, .category_id = EventCategories::MAX_KILL,             .category = "MAX_KILL",             .type = "POG", .meta_data = ""             },
        { .points = -8, .category_id = EventCategories::MAX_SUICIDE,          .category = "MAX_SUICIDE",          .type = "POG", .meta_data = ""             },
        { .points = -8, .category_id = EventCategories::MAX_TEAM_KILL,        .category = "MAX_TEAM_KILL",        .type = "POG", .meta_data = ""             },
        { .points =  9, .category_id = EventCategories::BASE_CAPTURE,         .category = "BASE_CAPTURE",         .type = "POG", .meta_data = ""             },
        { .points = 18, .category_id = EventCategories::BASE_RECAPTURE,       .category = "BASE_RECAPTURE",       .type = "POG", .meta_data = ""             },
        { .points =  0, .category_id = EventCategories::BANNED_CLASS,         .category = "BANNED_CLASS",         .type = "POG", .meta_data = "MAX"          },
        { .points =  0, .category_id = EventCategories::BANNED_ITEM_CATEGORY, .category = "BANNED_ITEM_CATEGORY", .type = "POG", .meta_data = "Shotgun"      },
        { .points =  0, .category_id = EventCategories::BANNED_ITEM_CATEGORY, .category = "BANNED_ITEM_CATEGORY", .type = "POG", .meta_data = "Heavy Weapon" },
        { .points =  0, .category_id = EventCategories::BANNED_ITEM,          .category = "BANNED_ITEM",          .type = "POG", .meta_data = "Blackhand"    }
    };

    for(const auto &db_data : event_data)
    {
      model.Data = db_data;
      created_record_count += model.CreateRecord();
    }

    return created_record_count;
  }
}