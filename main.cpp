#include <iostream>
#include <thread>
#include <chrono>
#include <ApGame/Core/Application.hpp>

int run_overlay(ApGame::Core::Application& app)
{
  MSG msg = { nullptr };
  while(msg.message != WM_QUIT)
  {
    app.IsRunning() ? app.Run() : PostQuitMessage(0);


    // If there are Window messages then process them.
    if(PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ))
    {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  return (int)msg.wParam;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  ApGame::Core::Application app(hInstance);
  run_overlay(app);

  return 0;
}
