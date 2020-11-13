#ifndef APGAME_CONTENTS_SCORECONTENT_HPP
#define APGAME_CONTENTS_SCORECONTENT_HPP

#include <ApUI/Widgets/Layout/Group.hpp>
#include <ApUI/Widgets/Columns/Column.hpp>
#include <ApUI/Types/Color.hpp>

namespace ApGame::Contents
{
  class ScoreContent : public ApUI::Widgets::Layout::Group
  {
  public:
    struct TeamDataTemplate
    {
      std::string name;
      std::string tag;
      ApUI::Types::Color empire_color;
      std::vector<std::string> players;
    };
  public:
    ScoreContent();

  private:
    ApUI::Widgets::Columns::Column *m_team_header;
    ApUI::Widgets::Columns::Column *m_team_score;
    std::vector<TeamDataTemplate> m_teams;
  };
}

#endif // APGAME_CONTENTS_SCORECONTENT_HPP
