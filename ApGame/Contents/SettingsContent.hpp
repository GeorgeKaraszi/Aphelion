#ifndef APGAME_CONTENTS_SETTINGSCONTENT_HPP
#define APGAME_CONTENTS_SETTINGSCONTENT_HPP

#include <ApUI/Widgets/Layout/Group.hpp>
#include <ApUI/Widgets/Buttons/ButtonColored.hpp>
#include <ApUI/Widgets/InputFields/InputText.hpp>
#include <ApUI/Widgets/Sliders/Slider.hpp>

namespace ApGame::Contents
{
  class SettingsContent : public ApUI::Widgets::Layout::Group
  {
  public:
    explicit SettingsContent(int team_size = 1);

  private:
    void ModifyTeams(int amount);
    void AddTeams(int amount);
    void RemoveTeams(int amount);
    void SubmitTeams();
  public:
    int TeamSize;
    std::vector<std::string> TeamTags;
    ApTools::Eventing::Event<int>              TeamSizeChangedEvent;
    ApTools::Eventing::Event<int, std::string> TeamAddedEvent;

  private:
    ApUI::Widgets::Sliders::Slider<int>   *m_team_count { nullptr };
    ApUI::Widgets::Layout::Group          *m_team_group { nullptr };
    ApUI::Widgets::Buttons::ButtonColored *m_save_btn   { nullptr };
  };
}

#endif //APGAME_CONTENTS_SETTINGSCONTENT_HPP
