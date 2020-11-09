#ifndef APUI_PANELS_APANEL_HPP
#define APUI_PANELS_APANEL_HPP

#include <vector>
#include <unordered_map>
#include <ApUI/Plugins/IDrawable.hpp>
#include <ApUI/Widgets/WidgetContainer.hpp>
#include <ApTools/Eventing/Event.hpp>

namespace ApUI::Panels
{
  class APanel : public Plugins::IDrawable, public Widgets::WidgetContainer
  {
  public:
    explicit APanel(bool open = true);

    void Open();
    void Close();
    void SetOpen(bool open = true);
    [[nodiscard]]
    bool IsOpen() const;

    void Draw() override;

    [[nodiscard]]
    const std::string& GetPanelID() const;

  protected:
    virtual void _Draw_Impl();

  public:
    bool enabled = true;
    ApTools::Eventing::Event<> OpenEvent;
    ApTools::Eventing::Event<> CloseEvent;

  protected:
    std::string m_panelID;
    bool m_opened = true;

  private:
    static uint64_t __PANEL_ID_INCREMENT;
  };
}

#endif //APUI_PANELS_APANEL_HPP
