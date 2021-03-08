#include "WelcomeContent.hpp"
#include <ApCore/Core/Network.hpp>
#include <ApData/Sql/DbSeed.hpp>
#include <ApUI/Widgets/Texts/TextColored.hpp>


void InitializeDBThread(bool *db_completed, const ApData::Sql::DBSeed::ReporterCallback &callback)
{
  auto db     = ApData::Sql::Database::GetDatabase();
  auto census = ApCore::Core::Network::GetNetwork()->GetCensusAPI();

  ApData::Sql::DBSeed::InitializeTables(db->Get(), census, callback);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  (*db_completed) = true;
}

namespace ApGame::Contents
{
  WelcomeContent::WelcomeContent() : m_db_init(&CreateWidget<ApUI::Widgets::Layout::Group>())
  {
    m_db_init->CreateWidget<ApUI::Widgets::Texts::TextColored>("Initializing Database");

    ApData::Sql::DBSeed::ReporterCallback logger = [&](const std::string &log, bool error){
      auto txt_color = error ? ApUI::Types::Color::Red : ApUI::Types::Color::Yellow;
      m_db_init->CreateWidget<ApUI::Widgets::Texts::TextColored>(log, txt_color);
    };

    std::thread(InitializeDBThread, &m_db_finished, logger).detach();
  }

  void WelcomeContent::_Draw_Impl()
  {
    DrawWidgets();

    if(m_db_finished)
    {
      CompletedInitializingEvent.Invoke();
    }
  }
}