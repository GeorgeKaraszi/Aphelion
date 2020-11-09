#ifndef APUI_PLUGINS_ITRANSFORMABLE_HPP
#define APUI_PLUGINS_ITRANSFORMABLE_HPP

#include <ApUI/ImGui/imgui.h>

namespace ApUI::Plugins
{
  class ITransformable
  {
  public:
    ITransformable() = default;
    explicit ITransformable(ImVec2 size)
    : m_size(size)
    {}
    explicit ITransformable(ImVec2 size, ImVec2 position)
    : m_size(size), m_position(position)
    {}

    void SetPosition(ImVec2 position)
    {
      m_position = position;
    }

    void SetSize(ImVec2 size)
    {
      m_size = size;
    }

    void SetFlags(int flags)
    {
      m_flags = flags;
    }

    [[nodiscard]]
    ImVec2 GetPosition() const
    {
      return m_position;
    }

    [[nodiscard]]
    ImVec2 GetSize() const
    {
      return m_size;
    }

    [[nodiscard]]
    int GetFlags() const
    {
      return m_flags;
    }

  protected:
    virtual void Update() {};

  protected:
    ImVec2 m_size;
    ImVec2 m_position;
    int    m_flags = 0;
  };
}

#endif //APUI_PLUGINS_ITRANSFORMABLE_HPP
