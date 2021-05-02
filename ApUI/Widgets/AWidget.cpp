#include <ApInclude/pch.hpp>
#include "AWidget.hpp"


uint64_t ApUI::Widgets::AWidget::_WIDGET_ID_INCREMENT_ = 0;

namespace ApUI::Widgets
{
  AWidget::AWidget() : m_parent(nullptr)
  {
    widget_id = "##" + std::to_string(_WIDGET_ID_INCREMENT_++);
  }

  AWidget::AWidget(const char *id) : m_parent(nullptr), widget_id(id) {}

  void AWidget::Draw()
  {
    if(!enabled) return;

    BeginStyle();
    _Draw_Impl();
    EndStyle();

    if(m_auto_execute_plugins)
      ExecutePlugins();

    if(!lineBreak)
      ImGui::SameLine();
  }

  void AWidget::LinkTo(const AWidget &other)
  {
    widget_id = other.widget_id;
  }

  void AWidget::Destroy()
  {
    m_destroyed = true;
  }

  bool AWidget::IsDestroyed() const
  {
    return m_destroyed;
  }

  bool AWidget::HasParent() const
  {
    return PRESENT_PTR(m_parent);
  }

  void AWidget::SetParent(WidgetContainer *parent)
  {
    m_parent = parent;
  }

  WidgetContainer *AWidget::GetParent()
  {
    return m_parent;
  }

  bool AWidget::operator==(AWidget *other) const
  {
    return widget_id == other->widget_id && m_parent == other->m_parent;
  }
}
