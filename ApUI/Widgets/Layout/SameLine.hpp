#ifndef APUI_WIDGETS_LAYOUT_SAME_LINE_HPP
#define APUI_WIDGETS_LAYOUT_SAME_LINE_HPP

#include <ApUI/Widgets/DataWidget.hpp>

namespace ApUI::Widgets::Layout
{
  class SameLine : public DataWidget<ImVec2>
  {
  public:
    explicit SameLine(ImVec2 size = ImVec2(0, 0)) : DataWidget<ImVec2>(m_size), m_size(size) {}

  protected:
    void _Draw_Impl() override
    {
      ImGui::SameLine(m_size.x, m_size.y);
    }

  private:
    ImVec2 m_size;
  };
}

#endif //APUI_WIDGETS_LAYOUT_SAME_LINE_HPP
