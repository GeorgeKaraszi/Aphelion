#include <iostream>
#include <imgui/imgui.h>
#include <RendererD3D.hpp>


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);

  switch(msg)
  {
    // WM_ACTIVATE is sent when the window is activated or deactivated.
    // We pause the game when the window is deactivated and unpause it
    // when it becomes active.
    case WM_ACTIVATE:
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_MENUCHAR:      // Don't beep when we alt-enter.
      return MAKELRESULT(0, MNC_CLOSE);
    case WM_GETMINMAXINFO: // Catch this message so to prevent the window from becoming too small.
      ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
      ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
    case WM_SIZE:          // Save the new client area dimensions.
    case WM_ENTERSIZEMOVE: // WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
    case WM_EXITSIZEMOVE:  // User is done resizing the window
    default:
      break;
  }

  return DefWindowProc(hwnd, msg, wParam, lParam);
}

int run_overlay(const std::shared_ptr<ApWindow::RendererD3D>& renderer)
{
  MSG msg = { nullptr };
  while(msg.message != WM_QUIT)
  {
    // If there are Window messages then process them.
    if(PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ))
    {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }

    renderer->Render([] {});
  }
  return (int)msg.wParam;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

//  auto window = ApWindow::Window(hInstance);
//  if(!window.ApCreateWindow(WindowProc, "main"))
//  {
//    std::cout << "Could not create window!" << std::endl;
//    return 1;
//  }
//
//  run_overlay(std::make_shared<ApWindow::RendererD3D>(window));

  return 0;
}
