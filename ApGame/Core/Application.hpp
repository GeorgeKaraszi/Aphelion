#ifndef APGAME_CORE_APPLICATION_HPP
#define APGAME_CORE_APPLICATION_HPP

#include <ApWindow/Window.hpp>
#include <ApWindow/RendererD3D.hpp>
#include <ApUI/Core/UIManager.hpp>

namespace ApGame::Core
{
  class Application
  {
  public:
    Application() = delete;
    explicit Application(HINSTANCE hinst);

    void Run();
    bool IsRunning();

    static Application* GetApplication();

  private:
    void BuildCanvas();

  public:
    std::unique_ptr<ApWindow::Window>      window;
    std::unique_ptr<ApWindow::RendererD3D> renderer;
    std::unique_ptr<ApUI::Core::UIManager> uiManager;

  private:
    bool m_running = true;
    bool m_visible = true;
  };
}

#endif //APGAME_CORE_APPLICATION_HPP
