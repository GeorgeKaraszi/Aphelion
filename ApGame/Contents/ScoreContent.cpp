#include "ScoreContent.hpp"
#include <ApUI/Widgets/Buttons/ButtonColored.hpp>
#include <ApUI/Widgets/InputFields/InputText.hpp>
#include <iostream>

namespace ApGame::Contents
{
  ScoreContent::ScoreContent()
  {
    using namespace ApUI::Types;
    using namespace ApUI::Widgets;
    using namespace ApUI::Plugins;

    CreateWidget<Buttons::ButtonColored>("Test", ImVec2(-FLT_MIN, 30.0f), Color::Yellow, Color::Red);
    CreateWidget<Buttons::ButtonColored>("Score", ImVec2(-FLT_MIN, 30.0f), Color::Yellow, Color::Red);
    auto input = &CreateWidget<InputFields::InputText>("Prefilled Content", "My Label");

    auto &dataChangedDispatch = input->AddPlugin<DataDispatcher<std::string>>();

//    dataChangedDispatch.RegisterGatherer(
//        [&] ()->std::string
//        {
//          return "test content";
//        });

    dataChangedDispatch.RegisterProvider(
        [&](const std::string &content)
        {
          std::cout << "Entered Provider!: " << content << std::endl;
        });

    input->EnterPressedEvent += [&](const std::string& content)
    {
      std::cout << "Pressed Enter [Event]!: " << content  << std::endl;
    };
  }
}