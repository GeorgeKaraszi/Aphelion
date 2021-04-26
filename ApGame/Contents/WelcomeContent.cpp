#include "WelcomeContent.hpp"
#include <ApCore/Core/Network.hpp>
#include <ApData/Sql/DbSeed.hpp>
#include <ApUI/Widgets/Texts/TextColored.hpp>


void InitializeDBThread(bool *db_completed, const ApData::Sql::DBSeed::ReporterCallback &callback)
{
  auto db      = ApData::Sql::Database::GetDatabase();
  auto census  = ApCore::Core::Network::GetNetwork()->GetCensusAPI();
  auto db_seed = ApData::Sql::DBSeed(db->Get(), census.get(), callback);
  auto success = db_seed.InitializeTables();
//  std::this_thread::sleep_for(std::chrono::seconds(1));
  (*db_completed) = success;
}

namespace ApGame::Contents
{
  WelcomeContent::WelcomeContent() : m_db_init(&CreateWidget<ApUI::Widgets::Layout::Group>())
  {
    ApData::Sql::DBSeed::ReporterCallback logger = [&](const std::string &message, bool error) {
      AddLog(message, error);
    };

    if(ApCore::Core::Network::GetNetwork()->HasAPIKey())
    {
      AddLog("Initializing Database", false);
      std::thread(InitializeDBThread, &m_db_finished, logger).detach();
    }
    else
    {
      AddLog("[Error] Failed to load API key", true);
      AddLog(" - Register a new API key by creating one from http://census.daybreakgames.com");
      AddLog(" - Then save the API Key in a new api_key.txt file");
    }
  }

  void WelcomeContent::_Draw_Impl()
  {
    DrawWidgets();

    if(m_db_finished && !m_db_error)
    {
      CompletedInitializingEvent.Invoke();
    }
  }

  void WelcomeContent::AddLog(const std::string &message, bool error)
  {
    auto txt_color  = error ? ApUI::Types::Color::Red : ApUI::Types::Color::Yellow;
    m_db_error     |= error;
    m_db_init->CreateWidget<ApUI::Widgets::Texts::TextColored>(message, txt_color);
  }
}