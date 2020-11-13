#include "ChildWindow.hpp"


namespace ApUI::Widgets::Windows
{
  ChildWindow::ChildWindow(std::string name, ResizeWindowFlags size_flag, ImVec2 size)
  : name(std::move(name)), ResizeFlag(size_flag), Plugins::ITransformable(size)
  {
    SetFlags(ImGuiWindowFlags_NoDecoration);
  }

  void ChildWindow::Update()
  {
    if(ResizeFlag == ApUIWindow_SizeByAvailableSpace)
    {
      SetSize(ImGui::GetContentRegionAvail());
    }
  }

  void ChildWindow::_Draw_Impl()
  {
    Update();

    if(ImGui::BeginChild(name.c_str(), GetSize(), ShowBoarder, GetFlags()))
    {
      DrawWidgets();
    }

    ImGui::EndChild();
  }

}