#ifndef APUI_PLUGINS_IPLUGIN_HPP
#define APUI_PLUGINS_IPLUGIN_HPP

namespace ApUI::Plugins
{
  class IPlugin
  {
  public:
    virtual void Execute() = 0;
    void *data = nullptr;
  };
}

#endif // APUI_PLUGINS_IPLUGIN_HPP
