#ifndef APWINDOW_RENDERERD3D_HPP
#define APWINDOW_RENDERERD3D_HPP

#include <ApInclude/pch.hpp>
#include <functional>

namespace ApWindow
{
  class RendererD3D
  {
  public:
    typedef typename std::function<void()> vRendererCallback;
  public:
    RendererD3D()                    = delete;
    RendererD3D(const RendererD3D &) = default;

    explicit RendererD3D(HWND hwnd, int width, int height);
    ~RendererD3D();

    ID3D11Device         *GetDevice()        { return m_Device; }
    ID3D11DeviceContext  *GetDeviceContext() { return m_DeviceContext; }
    IDXGISwapChain       *GetSwapChain()     { return m_SwapChain; }

    HRESULT Render(const vRendererCallback& callback);

    [[nodiscard]]
    bool IsShutDown() const;

    void ToggleVSync();

    void OnWindowResize(int width, int height);
    void ShutDown();

  private:
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
