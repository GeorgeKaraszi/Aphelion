#ifndef APUI_PANELS_APANEL_HPP
#define APUI_PANELS_APANEL_HPP

#include <vector>
#include <unordered_map>
#include <Plugins/IDrawable.hpp>

namespace ApUI::Panels
{
  class APanel : public Plugins::IDrawable
  {
  public:
    APanel();

    void Draw() override;

    [[nodiscard]]
    const std::string& GetPanelID() const;

  protected:
    virtual void _Draw_Impl() = 0;

  public:
    bool enabled = true;

  protected:
    std::string m_panelID;

  private:
    static uint64_t __PANEL_ID_INCREMENT;
  };
}

#endif //APUI_PANELS_APANEL_HPP
