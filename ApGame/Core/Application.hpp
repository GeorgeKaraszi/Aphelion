#ifndef APGAME_CORE_APPLICATION_HPP
#define APGAME_CORE_APPLICATION_HPP

#include <ApWindow/Window.hpp>
#include <ApWindow/RendererD3D.hpp>
#include <ApUI/Core/UIManager.hpp>
#include <ApGame/Panels/Menus/MainMenu.hpp>

namespace ApGame::Core
{
  class Application
  {
  public:
    Application() = delete;
    explicit Application(HINSTANCE hinst);

    void Run();

    [[nodiscard]]
    bool IsRunning() const;

    static Application* GetApplication();
  public:
    std::unique_ptr<ApWindow::Window>      window;
    std::unique_ptr<ApWindow::RendererD3D> renderer;
    std::unique_ptr<ApUI::Core::UIManager> uiManager;
    ApUI::Modules::Canvas                  canvas;

  private:
    Panels::Menus::MainMenu m_menu;
    bool m_running = true;
    bool m_visible = true;
  };
}

#endif //APGAME_CORE_APPLICATION_HPP
