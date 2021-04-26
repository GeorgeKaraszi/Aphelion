#ifndef APCORE_PLANETSIDE_AFACTION_HPP
#define APCORE_PLANETSIDE_AFACTION_HPP

#include <ApUI/Types/Color.hpp>

namespace ApCore::Planetside
{
  class AFaction
  {
  public:
    enum FACTION_ { FACTION_VS = 1,  FACTION_NC = 2, FACTION_TR = 3, FACTION_NSO = 4 };
    typedef int FactionT;

  public:
    [[nodiscard]]
    ApUI::Types::Color EmpireColor() const
    {
      switch(faction)
      {
        case FACTION_VS:
          return ApUI::Types::Color::Faction_VS;
        case FACTION_NC:
          return ApUI::Types::Color::Faction_NC;
        default:
          return ApUI::Types::Color::Faction_TR;
      }
    }

  protected:
    void SetFaction(int faction_id)  { faction = Faction(faction_id); }
    void SetFaction(char faction_id) { faction = Faction((int)faction_id - (int)'0'); }
    static FactionT Faction(int faction_id)
    {
      switch(faction_id)
      {
        case 1:
          return FACTION_VS;
        case 2:
          return FACTION_NC;
        case 3:
          return FACTION_TR;
        default:
          return FACTION_NSO;
      }
    }

  public:
    FactionT faction{};
  };
}

#endif //APCORE_PLANETSIDE_AFACTION_HPP
