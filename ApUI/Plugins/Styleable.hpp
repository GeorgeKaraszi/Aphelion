#ifndef APUI_PLUGINS_STYLEABLE_HPP
#define APUI_PLUGINS_STYLEABLE_HPP

#include <vector>
#include <ApUI/ImGui/imgui.h>

namespace ApUI::Plugins
{
  class Styleable
  {
  public:
    void AddStyle(ImGuiCol idx, ImVec4 color)
    {
      m_styles.emplace_back(idx, color);
    }

    void RemoveAllStyles()
    {
      m_styles.clear();
    }

  protected:
    void BeginStyle()
    {
      for(auto &[idx, color] : m_styles)
      {
        ImGui::PushStyleColor(idx, color);
      }
    }

    void EndStyle()
    {
      ImGui::PopStyleColor(m_styles.size());
    }

  protected:
    std::vector<std::pair<ImGuiCol, ImVec4>> m_styles;
  };
}

#endif //APUI_PLUGINS_STYLEABLE_HPP
