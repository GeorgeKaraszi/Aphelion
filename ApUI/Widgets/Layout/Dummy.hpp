#ifndef APUI_WIDGETS_LAYOUT_DUMMY_HPP
#define APUI_WIDGETS_LAYOUT_DUMMY_HPP

#include <ApUI/Widgets/AWidget.hpp>

namespace ApUI::Widgets::Layout
{
  class Dummy : public AWidget
  {
  public:
    explicit Dummy(ImVec2 size) : m_size(size) {}

  protected:
    void _Draw_Impl() override
    {
      ImGui::Dummy(m_size);
    }

  private:
    ImVec2 m_size;
  };
}

#endif //APUI_WIDGETS_LAYOUT_DUMMY_HPP
