#include "Application.hpp"

static ApGame::Core::Application *g_application = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  // TODO: Don't allow ImGui to process inputs if windows with inputs are not active.
  ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);

  switch(msg)
  {
    // TODO: Deal with window resizing (like game rez changes ect..)
    case WM_ACTIVATE:
    case WM_SIZE:
    case WM_ENTERSIZEMOVE:
    case WM_EXITSIZEMOVE:
    case WM_GETMINMAXINFO:
      return 0;
    case WM_MENUCHAR:
      return MAKELRESULT(0, MNC_CLOSE);  // Don't beep when we alt-enter.
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      break;
  }

  return DefWindowProc(hwnd, msg, wParam, lParam);
}

namespace ApGame::Core
{
  Application::Application(HINSTANCE hinst)
  {
    window    = std::make_unique<ApWindow::Window>(hinst, WindowProc, "MainOverlay");
    renderer  = std::make_unique<ApWindow::RendererD3D>(window->GetMainWnd(), window->GetWidth(), window->GetHeight());
    uiManager = std::make_unique<ApUI::Core::UIManager>(
        window->GetMainWnd(),
        renderer->GetDevice(),
        renderer->GetDeviceContext(),
        static_cast<float>(window->GetWidth()),
        static_cast<float>(window->GetHeight())
    );

    renderer->RenderEvent += [uiContainer = uiManager.get()] { uiContainer->Render(); };

    auto *panel = &m_menu;
    auto *io    = &ImGui::GetIO();
    auto pos    = ImVec2(io->DisplaySize.x/4,  io->DisplaySize.y/4);
    auto size   = ImVec2(io->DisplaySize.x/1.5f, io->DisplaySize.y/2);
    panel->SetPosition(pos);
    panel->SetSize(size);
    canvas.AddPanel(*panel);
    uiManager->SetCanvas(canvas);
    g_application = this;
  }

  void Application::Run() const
  {
    if(IsRunning() && window->IsVisible() && !renderer->IsShutDown())
    {
      renderer->Render();
    }
  }

  bool Application::IsRunning() const
  {
    return m_running;
  }

  Application *Application::GetApplication()
  {
    return g_application;
  }
}