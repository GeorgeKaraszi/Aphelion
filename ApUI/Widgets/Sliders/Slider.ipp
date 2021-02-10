namespace ApUI::Widgets::Sliders
{
  template<typename T>
  Slider<T>::Slider(const char* label, T min, T max)
    : Slider(label, min, max, min)
  {}

  template <typename T>
  Slider<T>::Slider(const char* label, T min, T max, T current)
    : DataWidget<T>(content),
      label(label),
      Min(min),
      Max(max),
      content(current)
  {}

  template <typename T>
  void Slider<T>::_Draw_Impl()
  {
    if(left_label)
    {
      ImGui::Text("%s", label.c_str());
      ImGui::SameLine();
    }

    bool content_changed = ImGui::SliderScalar(
        left_label ? "" : label.c_str(),
        _data_type(),
        &content,
        &Min,
        &Max,
        _format(),
        GetFlags()
        );

    if(content_changed)
    {
      ContentChangedEvent.Invoke(content);
      this->NotifyChange();
    }
  }

  template <>
  inline const char * Slider<float>::_format()
  {
    return "%e";
  }

  template <>
  inline const char * Slider<int>::_format()
  {
    return "%u";
  }

  template <>
  inline const char * Slider<short>::_format()
  {
    return "%d";
  }

  template <>
  inline ImGuiDataType Slider<float>::_data_type()
  {
    return ImGuiDataType_Float;
  }

  template <>
  inline ImGuiDataType Slider<int>::_data_type()
  {
    return ImGuiDataType_S32;
  }

  template <>
  inline ImGuiDataType Slider<short>::_data_type()
  {
    return ImGuiDataType_S8;
  }



}