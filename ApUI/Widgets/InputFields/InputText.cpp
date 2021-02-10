#include "InputText.hpp"

#include <utility>

namespace ApUI::Widgets::InputFields
{
  static int TabWasPressedCallback(ImGuiInputTextCallbackData *data)
  {
    if(data->EventKey == ImGuiKey_Tab)
    {
      auto input = (InputText*)data->UserData;
      input->EnterPressedEvent.Invoke(input->content);
      ImGui::ClearActiveID(); // Clear Focus on current element
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
    std::string previousContent = content;
    content.resize(maxInput, '\0');

    if(left_label)
    {
      ImGui::Text("%s", label.c_str());
      ImGui::SameLine();
    }

    ImGui::PushID(widget_id.c_str());
    bool enterPressed = ImGui::InputTextEx(
        left_label ? "" : label.c_str(),
        nullptr,
        &content[0],
        maxInput,
        GetSize(),
        GetFlags() | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion,
        TabWasPressedCallback,
        this
    );
    ImGui::PopID();

    // Ensures when we resize (via .resize/2 or when a user backspaces)
    // we can clear out everything beyond the null-terminator
    content = content.c_str(); // NOLINT(readability-redundant-string-cstr)

    if (content != previousContent)
    {
      ContentChangedEvent.Invoke(content);
      this->NotifyChange();
    }

    if (enterPressed)
      EnterPressedEvent.Invoke(content);
  }

}