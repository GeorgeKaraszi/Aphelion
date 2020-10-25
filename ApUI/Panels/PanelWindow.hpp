#ifndef APUI_PANELS_PANELWINDOW_HPP
#define APUI_PANELS_PANELWINDOW_HPP

#include <ApUI/ImGui/imgui.h>
#include <ApTools/Eventing/Event.hpp>
#include "APanel.hpp"

namespace ApUI::Panels
{
  class PanelWindow : public APanel
  {
  public:
    explicit PanelWindow(std::string name, bool open = true);
    PanelWindow(std::string name, ImVec2 minSize, ImVec2 maxSize, bool open = true);

    void Open();
    void Close();
    void SetOpen(bool open = true);

    [[nodiscard]]
    bool IsOpen() const;
    [[nodiscard]]
    bool IsHovered() const;

    void SetPosition(ImVec2 position);
    void SetSize(ImVec2 size);

    [[nodiscard]]
    ImVec2 GetPosition() const;
    [[nodiscard]]
    ImVec2 GetSize() const;
//    void SetAlignment(ImVec2 alignment);

  protected:
    void Update();
    void _Draw_Impl() override;

  public:
    std::string name;
    ImVec2 minSize = { 0, 0 };
    ImVec2 maxSize = { 10000.0f, 10000.0f };

    ApTools::Eventing::Event<> OpenEvent;
    ApTools::Eventing::Event<> CloseEvent;

  protected:
    ImVec2 m_position;
    ImVec2 m_size;

  private:
    bool m_opened  = true;
    bool m_hovered = false;

  };
}

#endif //APUI_PANELS_PANELWINDOW_HPP
