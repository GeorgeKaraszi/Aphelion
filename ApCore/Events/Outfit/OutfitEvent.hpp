#ifndef APCORE_EVENTS_OUTFIT_OUTFITEVENT_HPP
#define APCORE_EVENTS_OUTFIT_OUTFITEVENT_HPP

#include <ApCore/Events/AEvent.hpp>

namespace ApCore::Events::Outfit
{
  class OutfitEvent : public ApCore::Events::AEvent
  {
  public:
    explicit OutfitEvent(Core::TeamManager *manager);
  protected:
    void _load_rules_impl()                                override {};
    std::vector<std::string> _trackable_event_names_impl() override;
    bool _death_event_impl(const JSON& payload)            override;
    bool _revive_tick_event_impl(const JSON& payload)      override;
    bool _heal_tick_event_impl(const JSON& payload)        override;
  };
}

#endif //APCORE_EVENTS_OUTFIT_OUTFITEVENT_HPP
