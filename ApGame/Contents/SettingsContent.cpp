#include "SettingsContent.hpp"

namespace ApGame::Contents
{
  SettingsContent::SettingsContent(int team_size) : TeamSize(team_size)
  {
    using namespace ApUI;
    using namespace ApUI::Widgets;
    m_team_count = &CreateWidget<Sliders::Slider<int>>("Team count", 0, 2, team_size);
    m_team_group = &CreateWidget<Layout::Group>();
    m_save_btn   = &CreateWidget<Buttons::ButtonColored>("Save", Types::Color::Green, Types::Color::Blue);

    m_team_count->ContentChangedEvent += [&](int size) { ModifyTeams(size); };
    m_save_btn->ClickEvent            += [&]()         { SubmitTeams();     };
    m_save_btn->AppendFlags(ImGuiButtonFlags_AlignTextBaseLine);

    ModifyTeams(TeamSize);
  }

  void SettingsContent::ModifyTeams(int size)
  {
    int size_diff = size - (int)m_team_group->GetWidgets().size();
    TeamSize      = size;

    if(size_diff > 0)
    {
      AddTeams(size_diff);
    }

    if(size_diff < 0)
    {
      RemoveTeams(std::abs(size_diff));
    }

    TeamTags.resize(TeamSize);

    if(size_diff != 0)
    {
      TeamSizeChangedEvent.Invoke(TeamSize);
    }
  }

  void SettingsContent::AddTeams(int amount)
  {
    auto team_id = (int)m_team_group->GetWidgets().size();

    for(int i = 0; i < amount; i++, team_id++)
    {
      auto team_id_str = "team " + std::to_string(team_id + 1);
      auto team        = &m_team_group->CreateWidget<ApUI::Widgets::InputFields::InputText>("", team_id_str);
      team->maxInput   = 5;
      team->ContentChangedEvent += [&, team_id](const std::string &tag) {
        TeamTags[team_id] = tag;
      };
    }
  }

  void SettingsContent::RemoveTeams(int amount)
  {
    auto widgets = m_team_group->GetWidgets();
    int i = 0;
    for(auto it = widgets.rbegin(); it != widgets.rend() || i < amount; ++it, ++i)
    {
      (*it)->Destroy();
    }
  }

  void SettingsContent::SubmitTeams()
  {
    for(int i = 0; i < TeamTags.size(); i++)
    {
      TeamAddedEvent.Invoke(i, TeamTags[i]);
    }
  }
}