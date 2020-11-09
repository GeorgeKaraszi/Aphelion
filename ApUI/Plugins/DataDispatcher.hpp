#ifndef APUI_PLUGINS_DATADISPATCHER_HPP
#define APUI_PLUGINS_DATADISPATCHER_HPP

#include <functional>
#include <ApInclude/macros.h>
#include "IPlugin.hpp"

#define TRY_GATHER(type, output)  if (auto plugin = GetPlugin<ApUI::Plugins::DataDispatcher<type>>(); plugin && plugin->GatherEnabled) output = plugin->Gather();
#define TRY_PROVIDE(type, output) if (auto plugin = GetPlugin<ApUI::Plugins::DataDispatcher<type>>(); plugin) plugin->Provide(output);
#define TRY_NOTIFY_CHANGE(type)   if (auto plugin = GetPlugin<ApUI::Plugins::DataDispatcher<type>>(); plugin) plugin->NotifyChange();

namespace ApUI::Plugins
{
  template <typename T>
  class DataDispatcher : public IPlugin
  {
  public:
    void RegisterReference(T& reference)
    {
      m_dataPointer = &reference;
    }

    void RegisterProvider(std::function<void(T)> provider)
    {
      m_provider = provider;
    }

    void RegisterGatherer(std::function<T(void)> gatherer)
    {
      m_gatherer    = gatherer;
      GatherEnabled = true;
    }

    void Provide(T data)
    {
      if(m_valueChanged)
      {
        if(PRESENT_PTR(m_dataPointer))
        {
          *m_dataPointer = data;
        }
        else
        {
          m_provider(data);
        }

        m_valueChanged = false;
      }
    }

    void NotifyChange()
    {
      m_valueChanged = true;
    }

    T Gather()
    {
      return PRESENT_PTR(m_dataPointer) ? *m_dataPointer : m_gatherer();
    }

    void Execute() override {}

  public:
    bool GatherEnabled = false;

  private:
    bool m_valueChanged = false;
    T* m_dataPointer    = nullptr;
    std::function<void(T)> m_provider;
    std::function<T(void)> m_gatherer;
  };
}

#endif //APUI_PLUGINS_DATADISPATCHER_HPP
