#ifndef APUI_WIDGETS_SLIDERS_SLIDER_HPP
#define APUI_WIDGETS_SLIDERS_SLIDER_HPP

#include <ApTools/Eventing/Event.hpp>
#include <ApUI/Widgets/DataWidget.hpp>
#include <ApUI/Plugins/ITransformable.hpp>

namespace ApUI::Widgets::Sliders
{
  template <typename T> struct Allowed;
  template<> struct Allowed<float>  {};
  template<> struct Allowed<int>    {};
  template<> struct Allowed<short>  {};

  template <typename T>
  class Slider : public DataWidget<T>, public Plugins::ITransformable, private Allowed<T>
  {
  public:
    Slider(const char *label, T min, T max);
    Slider(const char *label, T min, T max, T current);

  protected:
    void _Draw_Impl() override;

  private:
    const char* _format();
    ImGuiDataType _data_type();

  public:
    bool left_label = true;
    std::string label;
    T Min;
    T Max;
    T content;
    ApTools::Eventing::Event<T> ContentChangedEvent;
  };
}

#include "Slider.ipp"
#endif //APUI_WIDGETS_SLIDERS_SLIDER_HPP
