#ifndef APGAME_CONTENTS_SCORECONTENT_HPP
#define APGAME_CONTENTS_SCORECONTENT_HPP

#include <ApUI/Widgets/Layout/Group.hpp>
#include <ApUI/Widgets/Tables/Table.hpp>
#include <ApUI/Types/Color.hpp>
#include <ApCore/Planetside/Team.hpp>
#include <ApCore/Core/TeamManager.hpp>

namespace ApGame::Contents
{
  class ScoreContent : public ApUI::Widgets::Layout::Group
  {
    using PS_TEAM_PTR = std::shared_ptr<ApCore::Planetside::Team>;
    using UI_N_TEAM   = std::pair<ApUI::Widgets::Layout::Group*, PS_TEAM_PTR>;
  public:
    ScoreContent();
    void ResizeTeams(int size);
    void RegisterTeam(int idx, const std::string &tag);

  private:
    void RecreateTeams();
    void _Draw_Impl() override;

  public:
    ApCore::Core::TeamManager TeamManager;
  };
}

#endif // APGAME_CONTENTS_SCORECONTENT_HPP
