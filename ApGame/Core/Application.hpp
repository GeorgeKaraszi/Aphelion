#ifndef APGAME_CORE_APPLICATION_HPP
#define APGAME_CORE_APPLICATION_HPP
#include <ApCore/Core/Network.hpp>
#include <ApWindow/Window.hpp>
#include <ApWindow/RendererD3D.hpp>
#include <ApUI/Core/UIManager.hpp>
#include <ApData/Sql/Database.hpp>
#include "MenuContainer.hpp"

namespace ApGame::Core
{
  class Application
  {
  public:
    Application() = delete;
    Application(const Application &) = delete;
    explicit Application(HINSTANCE hinst);

    void Run() const;

    [[nodiscard]]
    bool IsRunning() const;

    static Application* GetApplication();
  public:
    std::shared_ptr<ApCore::Core::Network> network;
    std::shared_ptr<ApData::Sql::Database> db;
    std::unique_ptr<ApWindow::Window>      window;
    std::unique_ptr<ApWindow::RendererD3D> renderer;
    std::unique_ptr<ApUI::Core::UIManager> uiManager;
    ApUI::Modules::Canvas                  canvas;


  private:
    MenuContainer *m_menu;
    bool m_running = true;
    bool m_visible = true;
  };
}

#endif //APGAME_CORE_APPLICATION_HPP
