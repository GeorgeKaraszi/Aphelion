#include "ChildWindow.hpp"


namespace ApUI::Widgets::Windows
{
  ChildWindow::ChildWindow(std::string name, ImVec2 size, bool boarder)
  : name(std::move(name)), Plugins::ITransformable(size), m_boarder(boarder)
  {
    SetFlags(ImGuiWindowFlags_NoDecoration);
  }

  void ChildWindow::_Draw_Impl()
  {
    if(ImGui::BeginChild(name.c_str(), GetSize(), m_boarder, GetFlags()))
    {
      DrawWidgets();
    }

    ImGui::EndChild();
  }

}