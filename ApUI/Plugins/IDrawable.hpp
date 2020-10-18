#ifndef APUI_PLUGINS_IDRAWABLE_HPP
#define APUI_PLUGINS_IDRAWABLE_HPP

namespace ApUI::Plugins
{
  class IDrawable
  {
  public:
    virtual void Draw() = 0;
  protected:
    virtual ~IDrawable() = default;
  };
}

#endif //APUI_PLUGINS_IDRAWABLE_HPP
