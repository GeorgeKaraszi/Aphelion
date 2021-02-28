#include <thread>
#include <chrono>
#include <ApGame/Core/Application.hpp>
#include <ApData/Sql/Database.hpp>
#include <ApData/Sql/DbSeed.hpp>

const static auto sleep_time = std::chrono::milliseconds(1);

void NetworkThread(ApGame::Core::Application *app)
{
  while (PRESENT_PTR(app) && app->IsRunning())
  {
    app->network->AsyncRun();
    std::this_thread::sleep_for(sleep_time);
  }
}

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

    std::this_thread::sleep_for(sleep_time);
  }

  return (int)msg.wParam;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  ApGame::Core::Application app(hInstance);

  ApData::Sql::Database db;
  ApData::Sql::DBSeed::InitializeTables(db, app.network->GetCensusAPI().get());

  std::thread(NetworkThread, &app).detach();
  run_overlay(app);

  return 0;
}
