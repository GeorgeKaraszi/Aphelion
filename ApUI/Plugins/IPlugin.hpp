#ifndef APHELION_APUI_PLUGINS_IPLUGIN_HPP
#define APHELION_APUI_PLUGINS_IPLUGIN_HPP

namespace Aphelion::ApUI::Plugins
{
  class IPlugin
  {
  public:
    virtual void Execute() = 0;
    void *data = nullptr;
  };
}

#endif //APHELION_APUI_PLUGINS_IPLUGIN_HPP
