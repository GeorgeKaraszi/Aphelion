#include "InputText.hpp"

#include <utility>

namespace ApUI::Widgets::InputFields
{
  static int TabWasPressed(ImGuiInputTextCallbackData *data)
  {
    if(data->EventKey == ImGuiKey_Tab)
    {
      InputText *input = (InputText*)data->UserData;
      input->EnterPressedEvent.Invoke(input->content);
    }

    return 0;
  }

  InputText::InputText(std::string p_content, std::string p_label, ImVec2 size)
    : DataWidget(content),
      Plugins::ITransformable(size),
      content(std::move(p_content)),
      label(std::move(p_label))
  {}

  void InputText::_Draw_Impl()
  {
    int flags =  this->GetFlags() | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion;

    std::string previousContent = content;
    content.resize(maxInput, '\0');

    ImGui::PushID(m_widget_id.c_str());
    bool enterPressed   = ImGui::InputTextEx(label.c_str(), nullptr, &content[0], maxInput, GetSize(), flags, TabWasPressed, this);
    ImGui::PopID();
    content = content.c_str();

    if (content != previousContent)
    {
      ContentChangedEvent.Invoke(content);
      this->NotifyChange();
    }

    if (enterPressed)
      EnterPressedEvent.Invoke(content);
  }

}