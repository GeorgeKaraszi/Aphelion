#include "Window.hpp"
#include <shellapi.h>
#include <commctrl.h>

#define AP_UID 666

namespace ApWindow
{
  Window::Window(HINSTANCE inst, bool primary_screen)
  : m_appInst(inst), m_window_visible(true)
  {
    auto display   = CSysDisplays();
    m_monitor_info = primary_screen ? display.GetPrimary() : display.GetSecondary();
  }

  Window::Window(HINSTANCE inst, WNDPROC lpWndProc, const wchar_t *name, bool primary_screen)
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

  bool Window::AddNotificationIcon(HWND hwnd)
  {
      NOTIFYICONDATA nid = { sizeof(nid) };
      nid.hWnd             = hwnd;
      nid.uFlags           = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP | NIF_GUID;
      nid.uID              = AP_UID;
      nid.uCallbackMessage = WMAPP_NOTIFYCALLBACK;
      LoadIconMetric(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDI_NOTIFICATIONICON), LIM_SMALL, &nid.hIcon);
      Shell_NotifyIcon(NIM_ADD, &nid);

      nid.uVersion = NOTIFYICON_VERSION_4;
      return Shell_NotifyIcon(NIM_SETVERSION, &nid);
  }

  void Window::DeleteNotificationIcon()
  {
    NOTIFYICONDATA nid = { sizeof(nid) };
    nid.uFlags         = NIF_GUID;
    nid.uID            = AP_UID;
    Shell_NotifyIcon(NIM_DELETE, &nid);
  }

  void Window::ShowContextMenu(HWND hwnd)
  {
    auto hMenu = LoadMenu(m_appInst, MAKEINTRESOURCE(IDC_CONTEXTMENU));
    if (hMenu)
    {
      HMENU hSubMenu = GetSubMenu(hMenu, 0);
      if (hSubMenu)
      {
        // our window must be foreground before calling TrackPopupMenu or the menu will not disappear when the user clicks away
        SetForegroundWindow(hwnd);

        // respect menu drop alignment
        UINT uFlags = TPM_RIGHTBUTTON;
        if (GetSystemMetrics(SM_MENUDROPALIGNMENT))
        {
          uFlags |= TPM_RIGHTALIGN;
        }
        else
        {
          uFlags |= TPM_LEFTALIGN;
        }

        POINT pt;
        GetCursorPos(&pt);
        TrackPopupMenu(hSubMenu, uFlags, pt.x, pt.y, 0, hwnd, nullptr);
      }
      DestroyMenu(hMenu);
    }
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

  HWND Window::MakeWindow(WNDPROC lpWndProc, const wchar_t *name)
  {
    HWND target;
    WNDCLASSEX wcex;
    wcex.cbSize        = sizeof(WNDCLASSEX);
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = lpWndProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = m_appInst;
    wcex.hIcon         = LoadIcon(m_appInst, MAKEINTRESOURCE(IDI_NOTIFICATIONICON));
    wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) CreateSolidBrush(0);
    wcex.lpszMenuName  = nullptr;
    wcex.lpszClassName = name;
    wcex.hIconSm       = LoadIcon(m_appInst, MAKEINTRESOURCE(IDI_NOTIFICATIONICON));
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