#include "Window.hpp"
#include "../ApInclude/macros.h"

namespace ApWindow
{
  Window::Window(HINSTANCE inst, bool primary_screen)
  : m_appInst(inst), m_window_visible(true)
  {
    auto display   = CSysDisplays();
    m_monitor_info = primary_screen ? display.GetPrimary() : display.GetSecondary();
  }

  Window::Window(HINSTANCE inst, WNDPROC lpWndProc, const char *name, bool primary_screen)
  : Window(inst, primary_screen)
  {
    m_hwnd = MakeWindow(lpWndProc, name);
  }

  HWND Window::GetMainWnd()
  {
    return m_hwnd;
  }

  void Window::ToggleWindow()
  {
    // Implement later
  }

  bool Window::IsVisible() const
  {
    return m_window_visible && PRESENT_PTR(m_hwnd);
  }

  u_int Window::GetHeight()
  {
    return m_monitor_info.Height();
  }

  u_int Window::GetWidth()
  {
    return m_monitor_info.Width();
  }

  HWND Window::MakeWindow(WNDPROC lpWndProc, const char *name)
  {
    HWND target;
    WNDCLASSEX wcex;
    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = lpWndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = m_appInst;
    wcex.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) CreateSolidBrush(0);
    wcex.lpszMenuName  = nullptr;
    wcex.lpszClassName = name;
    wcex.hIconSm       = LoadIcon(nullptr, IDI_APPLICATION);
    if (!RegisterClassEx(&wcex))
    {
      return nullptr;
    }

    #if DEBUG_MODE
    auto win_attr = 0;//WS_EX_TOPMOST;
    #else
    auto win_attr = WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
    #endif

    target = CreateWindowEx(
        win_attr,
        name,
        name,
        WS_POPUP,
        m_monitor_info.GetRect()->left,
        m_monitor_info.GetRect()->top,
        m_monitor_info.Width(),
        m_monitor_info.Height(),
        nullptr,
        nullptr,
        m_appInst,
        nullptr
    );

    ShowWindow(target, SW_SHOW);
    UpdateWindow(target);

    const MARGINS Margin = { -1 };
    HR(DwmExtendFrameIntoClientArea(target, &Margin));

    return target;
  }
}