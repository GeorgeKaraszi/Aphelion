#include <iostream>
#include <ApInclude/string_helper.hpp>
#include "DbSeed.hpp"
#include "Models/Loadout.hpp"
#include "Models/ItemCategory.hpp"
#include "Models/Item.hpp"
#include "Models/Profile.hpp"
#include "Models/Faction.hpp"
#include "Models/Player.hpp"
#include "Models/Outfit.hpp"

int seed_factions(
    ApData::Sql::Models::Faction &model,
    const std::shared_ptr<ApCore::Nets::CensusAPI> &census,
    const ApData::Sql::DBSeed::ReporterCallback& reporter
  )
{
  int created_record_count = 0;
  auto faction_data = census->GetCensusQuery("/get/ps2:v2/faction", "?c:limit=5000");

  if(!faction_data.contains("faction_list") || !faction_data["faction_list"].is_array())
  {
    reporter(format_string("Error couldn't resolve Census Faction data!: %s", faction_data.dump().c_str()), true);
    return 0;
  }

  for(const auto& faction : faction_data["faction_list"])
  {
    try
    {
      model.Data.image_set_id.clear();
      model.Data.image_path.clear();
      model.Data.faction_id      = std::stoi(faction["faction_id"].get<std::string>());
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

int seed_profiles(
    ApData::Sql::Models::Profile &model,
    const std::shared_ptr<ApCore::Nets::CensusAPI> &census,
    const ApData::Sql::DBSeed::ReporterCallback& reporter
  )
{
  int created_record_count = 0;
  auto profile_data = census->GetCensusQuery(
      "/get/ps2:v2/profile",
      "?c:show=profile_id,profile_type_id,profile_type_description,faction_id,name.en,image_path&c:limit=5000"
      );

  if(!profile_data.contains("profile_list") || !profile_data["profile_list"].is_array())
  {
    reporter(format_string("Error couldn't resolve Census Profile data!: %s", profile_data.dump().c_str()), true);
    return 0;
  }

  for(const auto& profile : profile_data["profile_list"])
  {
    try
    {
      model.Data.profile_id      = std::stoi(profile["profile_id"].get<std::string>());
      model.Data.profile_type_id = std::stoi(profile["profile_type_id"].get<std::string>());
      model.Data.faction_id      = std::stoi(profile["faction_id"].get<std::string>());

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

int seed_loadouts(
    ApData::Sql::Models::Loadout &model,
    const std::shared_ptr<ApCore::Nets::CensusAPI> &census,
    const ApData::Sql::DBSeed::ReporterCallback& reporter
  )
{
  int created_record_count = 0;
  auto loadout_data = census->GetCensusQuery("/get/ps2:v2/loadout", "?c:limit=5000");
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
    reporter(format_string("Error couldn't resolve Census Loadout data!: %s", loadout_data.dump().c_str()), true);
    return 0;
  }

  for(const auto& loadout : loadout_data["loadout_list"])
  {
    try
    {
      model.Data.profile_id = std::stoi(loadout["profile_id"].get<std::string>());
      model.Data.faction_id = std::stoi(loadout["faction_id"].get<std::string>());
      model.Data.loadout_id = std::stoi(loadout["loadout_id"].get<std::string>());
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

int seed_categories(
    ApData::Sql::Models::ItemCategory &model,
    const std::shared_ptr<ApCore::Nets::CensusAPI> &census,
    const ApData::Sql::DBSeed::ReporterCallback& reporter
  )
{
  int created_record_count = 0;
  auto category_data = census->GetCensusQuery("/get/ps2:v2/item_category", "?c:show=item_category_id,name.en&c:limit=5000");

  if(!category_data.contains("item_category_list") || !category_data["item_category_list"].is_array())
  {
    reporter(format_string("Error couldn't resolve Item Category data!: %s", category_data.dump().c_str()), true);
    return 0;
  }

  for(const auto &item_category : category_data["item_category_list"])
  {
    try
    {
      model.Data.item_category_id = std::stoi(item_category["item_category_id"].get<std::string>());
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

u_long seed_items(
    ApData::Sql::Models::Item &model,
    const std::shared_ptr<ApCore::Nets::CensusAPI> &census,
    const ApData::Sql::DBSeed::ReporterCallback& reporter
  )
{
  int returned;
  unsigned long created_record_count = 0;
  unsigned long next_set             = 0;
  const char* census_template =
      "?c:join=weapon"\
      "&c:show=item_id,name.en,is_vehicle_weapon,item_category_id,faction_id,image_path"\
      "&c:has=item_category_id"\
      "&c:limit=5000"\
      "&c:start=%lu";

  do {
    std::string census_query = format_string(census_template, next_set);
    auto item_data           = census->GetCensusQuery("/get/ps2:v2/item", census_query);
    returned                 = item_data.contains("returned") ? item_data["returned"].get<int>() : 0;
    next_set                += returned;

    if(!item_data.contains("item_list") || !item_data["item_list"].is_array())
    {
      reporter(format_string("Error couldn't resolve Item Data!: %s", item_data.dump().c_str()), true);
      break;
    }

    for(auto item : item_data["item_list"])
    {
     try
     {
       model.Data.item_id           = std::stoi(item["item_id"].get<std::string>());
       model.Data.item_category_id  = std::stoi(item["item_category_id"].get<std::string>());
       model.Data.is_vehicle_weapon = item["is_vehicle_weapon"].get<std::string>() != "0";

       if(item.contains("faction_id") && item["faction_id"].is_string())
       {
         model.Data.faction_id = std::stoi(item["faction_id"].get<std::string>());
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

namespace ApData::Sql::DBSeed
{
  void InitializeTables(ApData::Sql::Database& db, const std::shared_ptr<ApCore::Nets::CensusAPI>& census)
  {
    InitializeTables(db, census, [](const std::string& message, bool error) { std::cout << message << std::endl; });
  }

  void InitializeTables(
      ApData::Sql::Database& db,
      const std::shared_ptr<ApCore::Nets::CensusAPI>& census,
      const ReporterCallback& reporter
    )
  {
    unsigned long total_records_created = 0;
    ApData::Sql::Models::Item         items_model(db);
    ApData::Sql::Models::ItemCategory category_model(db);
    ApData::Sql::Models::Loadout      loadout_model(db);
    ApData::Sql::Models::Profile      profile_model(db);
    ApData::Sql::Models::Faction      faction_model(db);
    ApData::Sql::Models::Player(db).CreateTable();
    ApData::Sql::Models::Outfit(db).CreateTable();

    if(items_model.CreateTable())
    {
      reporter("Seeding Item's DB: This might take a while!", false);
      auto rec_count = seed_items(items_model, census, reporter);
      total_records_created += rec_count;
      reporter(format_string("- Created %lu Item Category Records", rec_count), false);
    }

    if(faction_model.CreateTable())
    {
      reporter("Seeding Faction DB:", false);
      auto rec_count = seed_factions(faction_model, census, reporter);
      total_records_created += rec_count;
      reporter(format_string("- Created %i Faction Records", rec_count), false);
    }

    if(profile_model.CreateTable())
    {
      reporter("Seeding Profile DB:", false);
      auto rec_count = seed_profiles(profile_model, census, reporter);
      total_records_created += rec_count;
      reporter(format_string("- Created %i Profile Records", rec_count), false);
    }

    if(loadout_model.CreateTable())
    {
      reporter("Seeding Loadout DB:", false);
      auto rec_count = seed_loadouts(loadout_model, census, reporter);
      total_records_created += rec_count;
      reporter(format_string("- Created %i Loadout Records", rec_count), false);
    }

    if(category_model.CreateTable())
    {
      reporter("Seeding Item Category DB:", false);
      auto rec_count = seed_categories(category_model, census, reporter);
      total_records_created += rec_count;
      reporter(format_string("- Created %i Item Category Records", rec_count), false);
    }

    reporter(format_string("Created %lu New Records in the DB", total_records_created), false);
  }
}