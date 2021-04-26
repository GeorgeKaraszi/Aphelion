#ifndef APCORE_EVENTS_POG_POGEVENT_HPP
#define APCORE_EVENTS_POG_POGEVENT_HPP

#include <ApCore/Events/AEvent.hpp>
#include <ApCore/Planetside/Team.hpp>
#include <ApData/Sql/Query/PogQuery.hpp>

namespace ApCore::Events::POG
{
  class PogEvent : public ApCore::Events::AEvent
  {
    using ApCore::Events::AEvent::AEvent;
  public:
    void Reset() override;

  protected:
    std::vector<std::string> _trackable_event_names_impl() override;
    void _load_rules_impl()                                override;
    bool _base_capture_event_impl(const JSON& payload)     override;
    bool _death_event_impl(const JSON& payload)            override;

  private:
    Planetside::Team *m_current_team { nullptr };
    ApData::Sql::Query::PogQuery::PogRules m_rules;
  };
}

#endif //APCORE_EVENTS_POG_POGEVENT_HPP
