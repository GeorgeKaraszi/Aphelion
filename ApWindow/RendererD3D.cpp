#include "RendererD3D.hpp"

namespace ApWindow
{
  RendererD3D::RendererD3D(HWND hwnd, int width, int height)
  {
    UINT createDeviceFlags = 0;
    #if DEBUG_MODE
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    #endif

    D3D_FEATURE_LEVEL featureLevel;
    D3D11CreateDevice(
        nullptr,                 // default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,                 // no software device
        createDeviceFlags,
        nullptr,
        0,                       // default feature level array
        D3D11_SDK_VERSION,
        &m_Device,
        &featureLevel,
        &m_DeviceContext
                     );

    HR(m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_MSAAQualtiy));

    IDXGIDevice* dxgiDevice = nullptr;
    HR(m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

    IDXGIAdapter* dxgiAdapter = nullptr;
    HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

    IDXGIFactory* dxgiFactory = nullptr;
    HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

    {
      DXGI_SWAP_CHAIN_DESC swapdesc;
      ZeroMemory(&swapdesc, sizeof(DXGI_SWAP_CHAIN_DESC));
      swapdesc.Windowed                           = true;
      swapdesc.OutputWindow                       = hwnd;
      swapdesc.BufferDesc.Width                   = width;
      swapdesc.BufferDesc.Height                  = height;
      swapdesc.BufferDesc.RefreshRate.Numerator   = 75;
      swapdesc.BufferDesc.RefreshRate.Denominator = 1;
      swapdesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
      swapdesc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
      swapdesc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
      swapdesc.SampleDesc.Count                   = 4;
      swapdesc.SampleDesc.Quality                 = m_MSAAQualtiy - 1;
      swapdesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
      swapdesc.BufferCount                        = 1;
      swapdesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
      swapdesc.Flags                              = 0;
      HR(dxgiFactory->CreateSwapChain(m_Device, &swapdesc, &m_SwapChain));
    }

    ReleaseCOM(dxgiDevice)
    ReleaseCOM(dxgiAdapter)
    ReleaseCOM(dxgiFactory)

    {
      D3D11_BLEND_DESC desc;
      ZeroMemory(&desc, sizeof(desc));
      desc.AlphaToCoverageEnable                 = false;
      desc.RenderTarget[0].BlendEnable           = true;
      desc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
      desc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
      desc.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
      desc.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_INV_DEST_ALPHA;
      desc.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_ONE;
      desc.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
      desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
      m_Device->CreateBlendState(&desc, &m_BlendState);
    }

    OnWindowResize(width, height);
  }

  RendererD3D::~RendererD3D()
  {
    ShutDown();
  }

  HRESULT RendererD3D::Render(const vRendererCallback& callback)
  {
    static float dx_bg_colors[4] = { 0.100f, 0.075f, 0.055f, 0.80f };

    if(m_IsShutdown)
    {
      return ERROR_GRAPHICS_TRY_AGAIN_LATER;
    }

    m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, dx_bg_colors);

    callback();

    return m_SwapChain->Present(m_vsync, 0);
  }

  void RendererD3D::ToggleVSync()
  {
    m_vsync = m_vsync == 0 ? 1 : 0;
  }

  void RendererD3D::OnWindowResize(int width, int height)
  {
    assert(m_DeviceContext);
    assert(m_Device);
    assert(m_SwapChain);

    if(PRESENT_PTR(m_RenderTargetView))
    {
      ReleaseCOM(m_RenderTargetView)
    }

    ID3D11Texture2D* backBuffer;
    HR(m_SwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
    HR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
    HR(m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView));
    ReleaseCOM(backBuffer)

    m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);
    {
      ZeroMemory(&m_Viewport, sizeof(D3D11_VIEWPORT));
      m_Viewport.TopLeftX = 0;
      m_Viewport.TopLeftY = 0;
      m_Viewport.Width    = static_cast<float>(width);
      m_Viewport.Height   = static_cast<float>(height);
      m_Viewport.MinDepth = 0.0f;
      m_Viewport.MaxDepth = 1.0f;
    }
    m_DeviceContext->RSSetViewports(1, &m_Viewport);
  }

  void RendererD3D::ShutDown()
  {
    if(m_IsShutdown) return;

    m_IsShutdown = true;

    if(PRESENT_PTR(m_DeviceContext))
    {
      m_DeviceContext->ClearState();
    }

    ReleaseCOM(m_Device)
    ReleaseCOM(m_SwapChain)
    ReleaseCOM(m_BlendState)
    ReleaseCOM(m_DeviceContext)
    ReleaseCOM(m_RenderTargetView)
  }
}
