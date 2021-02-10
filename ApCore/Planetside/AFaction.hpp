#ifndef APCORE_PLANETSIDE_AFACTION_HPP
#define APCORE_PLANETSIDE_AFACTION_HPP

#include <ApUI/Types/Color.hpp>

namespace ApCore::Planetside
{
  class AFaction
  {
  public:
    enum FACTION_ { FACTION_VS, FACTION_TR, FACTION_NC };
    typedef int FactionT;

  public:
    [[nodiscard]]
    ApUI::Types::Color EmpireColor() const
    {
      switch(faction)
      {
        case FACTION_NC:
          return ApUI::Types::Color::Faction_NC;
        case FACTION_TR:
          return ApUI::Types::Color::Faction_TR;
        default:
          return ApUI::Types::Color::Faction_VS;
      }
    }

  protected:
    void SetFaction(char faction_id) { faction = Faction(faction_id); }
    static FactionT Faction(char faction_id)
    {
      switch(faction_id)
      {
        case '1':
          return FACTION_VS;
        case '2':
          return FACTION_NC;
        default:
          return FACTION_TR;
      }
    }

  public:
    FactionT faction{};
  };
}

#endif //APCORE_PLANETSIDE_AFACTION_HPP
