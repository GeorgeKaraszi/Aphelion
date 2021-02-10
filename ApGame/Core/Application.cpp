#include <fstream>
#include <iostream>
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

std::string LoadApiKey()
{
  std::string api_key;
  std::ifstream api_key_file("api_key.txt", std::ifstream::in);
  if(api_key_file.is_open())
  {
    std::getline(api_key_file, api_key);
    boost::remove_erase_if(api_key, boost::is_any_of(" \n"));
    api_key_file.close();
  }
  else
  {
    assert(api_key_file.good() && "Could not find DBG API key file(api_key.txt).");
  }

  return api_key;
}

namespace ApGame::Core
{
  Application::Application(HINSTANCE hinst)
  {
    g_application = this;
    network   = std::make_shared<ApCore::Core::Network>(LoadApiKey());
    window    = std::make_unique<ApWindow::Window>(hinst, WindowProc, "MainOverlay", false);
    renderer  = std::make_unique<ApWindow::RendererD3D>(window->GetMainWnd(), window->GetWidth(), window->GetHeight());
    uiManager = std::make_unique<ApUI::Core::UIManager>(
        window->GetMainWnd(),
        renderer->GetDevice(),
        renderer->GetDeviceContext(),
        static_cast<float>(window->GetWidth()),
        static_cast<float>(window->GetHeight())
    );

    renderer->RenderEvent += [uiContainer = uiManager.get()] { uiContainer->Render(); };

    m_menu      = new MenuContainer();
    auto *panel = m_menu;
    auto *io    = &ImGui::GetIO();
    auto pos    = ImVec2(io->DisplaySize.x/4,  io->DisplaySize.y/4);
    auto size   = ImVec2(io->DisplaySize.x/1.5f, io->DisplaySize.y/2);
    panel->SetPosition(pos);
    panel->SetSize(size);
    canvas.AddPanel(*panel);
    uiManager->SetCanvas(canvas);
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
    return m_running && network->IsRunning();
  }

  Application *Application::GetApplication()
  {
    return g_application;
  }
}