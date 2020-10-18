#ifndef APWINDOW_RENDERERD3D_HPP
#define APWINDOW_RENDERERD3D_HPP

#include <pch.hpp>
#include <functional>
#include "Window.hpp"

namespace ApWindow
{
  class RendererD3D
  {
  public:
    struct ViewPointSize { float WIDTH, HEIGHT; };
    typedef typename std::function<void()> vRendererCallback;
  public:
    RendererD3D()                    = delete;
    RendererD3D(const RendererD3D &) = default;

    explicit RendererD3D(ApWindow::Window&);
    ~RendererD3D();

    auto *GetWindow()        { return &m_window; }
    auto *GetDevice()        { return m_Device; }
    auto *GetDeviceContext() { return m_DeviceContext; }
    auto *GetSwapChain()     { return m_SwapChain; }

    HRESULT Render(const vRendererCallback& callback);

    void ToggleVSync();

    [[maybe_unused]]
    ViewPointSize GetViewPortSize();
    void OnWindowResize();
    void OnWindowResize(int width, int height);
    void ShutDown();

  private:
    void InitializeRenderer();

  private:
    ApWindow::Window       m_window;
    bool                   m_IsShutdown        = false;
    u_int                  m_vsync             = 0;
    u_int                  m_MSAAQualtiy       = 3;
    ID3D11Device           *m_Device           = nullptr;
    ID3D11DeviceContext    *m_DeviceContext    = nullptr;
    IDXGISwapChain         *m_SwapChain        = nullptr;
    ID3D11BlendState       *m_BlendState       = nullptr;
    ID3D11RenderTargetView *m_RenderTargetView = nullptr;
    D3D11_VIEWPORT         m_Viewport{};
  };
}

#endif //APWINDOW_RENDERERD3D_HPP
