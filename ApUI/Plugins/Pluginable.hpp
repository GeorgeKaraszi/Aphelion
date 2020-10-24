#ifndef APHELION_APUI_PLUGINS_PLUGINABLE_HPP
#define APHELION_APUI_PLUGINS_PLUGINABLE_HPP

#include <vector>
#include "IPlugin.hpp"

namespace ApUI::Plugins
{
  class Pluginable
  {
  public:
    ~Pluginable()
    {
      RemoveAllPlugins();
    }

    template<typename T, typename... Args>
    T& AddPlugin(Args&& ... p_args)
    {
      static_assert(std::is_base_of<Plugins::IPlugin, T>::value, "T should derive from IPlugin");

      T* newPlugin = new T(std::forward<Args>(p_args)...);
      m_plugins.push_back(newPlugin);
      return *newPlugin;
    }

    /**
    * Returns the plugin of the given type, or nullptr if not found
    */
    template<typename T>
    T* GetPlugin()
    {
      static_assert(std::is_base_of<Plugins::IPlugin, T>::value, "T should derive from IPlugin");

      for(auto &m_plugin : m_plugins)
      {
        T* result = dynamic_cast<T*>(m_plugin);
        if (result)
          return result;
      }

      return nullptr;
    }

    /**
    * Execute every plugins
    */
    void ExecutePlugins()
    {
      for (auto& plugin : m_plugins)
        plugin->Execute();
    }

    /**
    * Remove every plugins
    */
    void RemoveAllPlugins()
    {
      for (auto &plugin : m_plugins)
      {
        delete plugin;
      }

      m_plugins.clear();
    }

  private:
    std::vector<IPlugin*> m_plugins;
  };
}

#endif //APHELION_APUI_PLUGINS_PLUGINABLE_HPP
