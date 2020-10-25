#ifndef APWINDOW_WINDOW_HPP
#define APWINDOW_WINDOW_HPP

#include <windows.h>
#include "Util/cmonitorinfo_ex.hpp"

namespace ApWindow
{
  class Window
  {
  public:
    Window()              = delete;
    Window(const Window&) = default;
    explicit Window(HINSTANCE inst, bool primary_screen = false);
    explicit Window(HINSTANCE inst, WNDPROC lpWndProc, const char *name);

    void ToggleWindow();

    [[nodiscard]]
    bool IsVisible() const;
    HWND GetMainWnd();

    u_int GetHeight();
    u_int GetWidth();

  private:
    HWND MakeWindow(WNDPROC lpWndProc, const char* name);

  private:
    HINSTANCE      m_appInst;
    CMonitorInfoEx m_monitor_info;
    bool           m_window_visible;
    HWND           m_hwnd = nullptr;
  };
}


#endif //APWINDOW_WINDOW_HPP
