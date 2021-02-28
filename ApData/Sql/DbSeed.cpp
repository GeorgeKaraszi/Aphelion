#include <iostream>
#include <ApInclude/string_helper.hpp>
#include "DbSeed.hpp"
#include "Models/Loadout.hpp"
#include "Models/ItemCategory.hpp"
#include "Models/Item.hpp"

void seed_loadouts(ApData::Sql::Models::Loadout &loadout_model)
{
  std::vector<ApData::Sql::Models::Loadout::TableData> loadout_data  = {
      { 1, 1, 2, 2,    "Infiltrator"},
      { 2, 3, 4, 2,    "Light Assault" },
      { 3, 4, 5, 2,    "Medic" },
      { 4, 5, 6, 2,    "Engineer" },
      { 5, 6, 7, 2,    "Heavy Assault" },
      { 6, 7, 8, 2,    "Max" },
      { 7, 8, 10, 3,   "Infiltrator"},
      { 8, 10, 12, 3,  "Light Assault" },
      { 9, 11, 13, 3,  "Medic" },
      { 10, 12, 14, 3, "Engineer" },
      { 11, 13, 15, 3, "Heavy Assault" },
      { 12, 14, 16, 3,  "Max" },
      { 13, 15, 17, 1,  "Infiltrator"},
      { 14, 17, 19, 1,  "Light Assault" },
      { 15, 18, 20, 1,  "Medic" },
      { 16, 19, 21, 1,  "Engineer" },
      { 17, 20, 22, 1,  "Heavy Assault" },
      { 18, 21, 23, 1,  "Max" }
  };

  for(auto data : loadout_data)
  {
    loadout_model.Data = data;
    loadout_model.CreateRecord();
  }
}

void seed_item_categories(ApData::Sql::Models::ItemCategory &item_cat_model)
{
  std::vector<ApData::Sql::Models::ItemCategory::TableData> item_category_data = {
      {1, 2, "Knife"},
      {2, 3, "Pistol"},
      {3, 4, "Shotgun"},
      {4, 5, "SMG"},
      {5, 6, "LMG"},
      {6, 7, "Assault Rifle"},
      {7, 8, "Carbine"},
      {8, 9, "AV MAX (Left)"},
      {9, 10, "AI MAX (Left)"},
      {10, 11, "Sniper Rifle"},
      {11, 12, "Scout Rifle"},
      {12, 13, "Rocket Launcher"},
      {13, 14, "Heavy Weapon"},
      {14, 15, "Flamethrower MAX"},
      {15, 16, "Flak MAX"},
      {16, 17, "Grenade"},
      {17, 18, "Explosive"},
      {18, 19, "Battle Rifle"},
      {19, 20, "AA MAX (Right)"},
      {20, 21, "AV MAX (Right)"},
      {21, 22, "AI MAX (Right)"},
      {22, 23, "AA MAX (Left)"},
      {23, 24, "Crossbow"},
      {24, 99, "Camo"},
      {25, 100, "Infantry"},
      {26, 101, "Vehicles"},
      {27, 102, "Infantry Weapons"},
      {28, 103, "Infantry Gear"},
      {29, 104, "Vehicle Weapons"},
      {30, 105, "Vehicle Gear"},
      {31, 106, "Armor Camo"},
      {32, 107, "Weapon Camo"},
      {33, 108, "Vehicle Camo"},
      {34, 109, "Flash Primary Weapon"},
      {35, 110, "Galaxy Left Weapon"},
      {36, 111, "Galaxy Tail Weapon"},
      {37, 112, "Galaxy Right Weapon"},
      {38, 113, "Galaxy Top Weapon"},
      {39, 114, "Harasser Top Gunner"},
      {40, 115, "Liberator Belly Weapon"},
      {41, 116, "Liberator Nose Cannon"},
      {42, 117, "Liberator Tail Weapon"},
      {43, 118, "Lightning Primary Weapon "},
      {44, 119, "Magrider Gunner Weapon"},
      {45, 120, "Magrider Primary Weapon"},
      {46, 121, "Mosquito Nose Cannon"},
      {47, 122, "Mosquito Wing Mount"},
      {48, 123, "Prowler Gunner Weapon"},
      {49, 124, "Prowler Primary Weapon"},
      {50, 125, "Reaver Nose Cannon"},
      {51, 126, "Reaver Wing Mount"},
      {52, 127, "Scythe Nose Cannon"},
      {53, 128, "Scythe Wing Mount"},
      {54, 129, "Sunderer Front Gunner"},
      {55, 130, "Sunderer Rear Gunner"},
      {56, 131, "Vanguard Gunner Weapon"},
      {57, 132, "Vanguard Primary Weapon"},
      {58, 133, "Implants"},
      {59, 134, "Consolidated Camo"},
      {60, 135, "VO Packs"},
      {61, 136, "Male VO Pack"},
      {62, 137, "Female VO Pack"},
      {63, 138, "Valkyrie Nose Gunner"},
      {64, 139, "Infantry Abilities"},
      {65, 140, "Vehicle Abilities"},
      {66, 141, "Boosts & Utilities"},
      {67, 142, "Consolidated Decal"},
      {68, 143, "Attachments"},
      {69, 144, "ANT Top Turret"},
      {70, 145, "ANT Utility"},
      {71, 147, "Aerial Combat Weapon"},
      {72, 148, "ANT Harvesting Tool"},
      {73, 157, "Hybrid Rifle"},
      {74, 207, "Weapon"},
      {75, 208, "Bastion Point Defense"},
      {76, 209, "Bastion Bombard"},
      {77, 210, "Bastion Weapon System"},
      {78, 211, "Colossus Primary Weapon"},
      {79, 212, "Colossus Front Right Weapon"},
      {80, 213, "Colossus Front Left Weapon"},
      {81, 214, "Colossus Rear Right Weapon"},
      {82, 215, "Colossus Rear Left Weapon"}
  };

  for(auto data : item_category_data)
  {
    item_cat_model.Data = data;
    item_cat_model.CreateRecord();
  }
}

void seed_items(ApData::Sql::Models::Item &item_model, ApCore::Nets::CensusAPI *census)
{
  int returned                = 0;
  unsigned long next_set      = 0;
  const char* census_template =
      "?c:join=weapon"\
      "&c:show=item_id,name.en,is_vehicle_weapon,item_category_id,faction_id,image_path"\
      "&c:has=item_category_id"\
      "&c:limit=5000"\
      "&c:start=%lu";

  do {
    std::string census_query = format_string(census_template, next_set);
    auto item_data           = census->GetCensusQuery("/get/ps2:v2/item", census_query);
    next_set                += 5000;
    returned                 = item_data.contains("returned") ? item_data["returned"].get<int>() : 0;

    if(!item_data.contains("item_list") || !item_data["item_list"].is_array())
    {
      std::cout << "Error couldn't resolve Census Item data!: " << std::endl << item_data.dump() << std::endl;
      break;
    }

    for(auto item : item_data["item_list"])
    {
     try
     {
       item_model.Data.item_id           = std::stoi(item["item_id"].get<std::string>());
       item_model.Data.item_category_id  = std::stoi(item["item_category_id"].get<std::string>());
       item_model.Data.is_vehicle_weapon = item["is_vehicle_weapon"].get<std::string>() != "0";

       if(item["faction_id"].is_string())
       {
         item_model.Data.faction_id = std::stoi(item["faction_id"].get<std::string>());
       }
       else
       {
         item_model.Data.faction_id = 0;
       }

       item["image_path"].get_to(item_model.Data.image_path);
       item["name"]["en"].get_to(item_model.Data.name);
     }
     catch(...)
     {
       continue;
     }

      item_model.CreateRecord();
    }
  } while(returned == 5000);

}

namespace ApData::Sql::DBSeed
{
  void InitializeTables(ApData::Sql::Database &db, ApCore::Nets::CensusAPI *census)
  {
    ApData::Sql::Models::Item         items_model(db);
    ApData::Sql::Models::ItemCategory item_cat_model(db);
    ApData::Sql::Models::Loadout      loadout_model(db);

    if(items_model.CreateTable())
    {
      seed_items(items_model, census);
    }

    if(item_cat_model.CreateTable())
    {
      seed_item_categories(item_cat_model);
    }

    if(loadout_model.CreateTable())
    {
      seed_loadouts(loadout_model);
    }
  }
}