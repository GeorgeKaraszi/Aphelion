#ifndef APUI_WIDGETS_INPUTFIELDS_INPUTTEXT_HPP
#define APUI_WIDGETS_INPUTFIELDS_INPUTTEXT_HPP

#include <ApTools/Eventing/Event.hpp>
#include <ApUI/Widgets/DataWidget.hpp>
#include <ApUI/Plugins/ITransformable.hpp>

namespace ApUI::Widgets::InputFields
{
  class InputText : public DataWidget<std::string>, public Plugins::ITransformable
  {
  public:
    explicit InputText(std::string p_content = "", std::string p_label = "", ImVec2 size = ImVec2(0, 0));
  protected:
    void _Draw_Impl() override;

  public:
    std::string content;
    std::string label;
    int maxInput    = 256;
    bool left_label = true;
    ApTools::Eventing::Event<std::string> ContentChangedEvent;
    ApTools::Eventing::Event<std::string> EnterPressedEvent;
  };
}

#endif //APUI_WIDGETS_INPUTFIELDS_INPUTTEXT_HPP
