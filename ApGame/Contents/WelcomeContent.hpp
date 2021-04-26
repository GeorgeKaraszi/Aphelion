#ifndef APGAME_CONTENTS_WELCOMECONTENT_HPP
#define APGAME_CONTENTS_WELCOMECONTENT_HPP

#include <ApUI/Widgets/Layout/Group.hpp>
#include <ApTools/Eventing/Event.hpp>

namespace ApGame::Contents
{
  class DatabaseInitializer;
  class WelcomeContent : public ApUI::Widgets::Layout::Group
  {
  public:
    WelcomeContent();

  protected:
    void _Draw_Impl() override;

  private:
    void AddLog(const std::string &message, bool error = false);

  public:
    ApTools::Eventing::Event<> CompletedInitializingEvent;
  private:
    bool m_db_finished                      = false;
    bool m_db_error                         = false;
    ApUI::Widgets::Layout::Group *m_db_init = nullptr;
  };
}

#endif //APGAME_CONTENTS_WELCOMECONTENT_HPP
