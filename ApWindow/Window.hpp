#ifndef APWINDOW_WINDOW_HPP
#define APWINDOW_WINDOW_HPP

#include <ApInclude/pch.hpp>
#include "Util/cmonitorinfo_ex.hpp"

#define WMAPP_NOTIFYCALLBACK WM_APP + 1

namespace ApWindow
{
  class Window
  {
  public:
    Window()              = delete;
    Window(const Window&) = default;
    explicit Window(HINSTANCE inst, bool primary_screen = false);
    explicit Window(HINSTANCE inst, WNDPROC lpWndProc, const wchar_t *name, bool primary_screen = false);

    void ToggleWindow();
    static bool AddNotificationIcon(HWND hwnd);
    static void DeleteNotificationIcon();
    void ShowContextMenu(HWND hwnd);

    [[nodiscard]]
    bool IsVisible() const;
    HWND GetMainWnd();

    u_int GetHeight();
    u_int GetWidth();

  private:
    HWND MakeWindow(WNDPROC lpWndProc, const wchar_t* name);

  private:
    HINSTANCE      m_appInst;
    CMonitorInfoEx m_monitor_info;
    bool           m_window_visible;
    HWND           m_hwnd = nullptr;
  };
}


#endif //APWINDOW_WINDOW_HPP
