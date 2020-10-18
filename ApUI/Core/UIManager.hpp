#ifndef APUI_CORE_UIMANAGER_HPP
#define APUI_CORE_UIMANAGER_HPP

#include <pch.hpp>
#include <Modules/Canvas.hpp>

namespace ApUI::Core
{
  class UIManager
  {
  public:
    UIManager()                 = delete;
    UIManager(const UIManager&) = delete;
    explicit UIManager(
        HWND hwnd,
        ID3D11Device *device,
        ID3D11DeviceContext *deviceContext,
        float width  = 0,
        float height = 0
    );

    ~UIManager();


    static void SetDisplaySize(float width, float height);
    void SetCanvas(Modules::Canvas &p_canvas);
    void RemoveCanvas();

    void Render();

  private:
    static void ApplyStyle();
  private:
    Modules::Canvas *m_currentCanvas = nullptr
  };
}

#endif //APUI_CORE_UIMANAGER_HPP
