#ifndef APUI_WIDGETS_AWIDGET_HPP
#define APUI_WIDGETS_AWIDGET_HPP

#include <string>
#include <ApUI/Plugins/Pluginable.hpp>
#include <ApUI/Plugins/IDrawable.hpp>
#include <ApUI/ImGui/imgui.h>
#include <ApUI/ImGui/imgui_internal.h>

namespace ApUI::Widgets
{
  class WidgetContainer;
  class AWidget : public Plugins::IDrawable, public Plugins::Pluginable
  {
  public:
    AWidget();
    virtual void Draw() override;

    void LinkTo(const AWidget &other);
    void Destroy();

    [[nodiscard]]
    bool IsDestroyed() const;
    [[nodiscard]]
    bool HasParent() const;

    void SetParent(WidgetContainer* parent);
    WidgetContainer* GetParent();

    bool operator==(AWidget* other) const;

  protected:
    virtual void _Draw_Impl() = 0;

  public:
    bool enabled = true;
    bool lineBreak = true;

  protected:
    WidgetContainer *m_parent;

    std::string m_widget_id;
    bool m_auto_execute_plugins = true;

  private:
    static uint64_t _WIDGET_ID_INCREMENT_;
    bool m_destroyed = false;
  };
}

#endif // APUI_WIDGETS_AWIDGET_HPP
