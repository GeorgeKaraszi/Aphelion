#ifndef APHELION_APUI_TYPES_COLOR_HPP
#define APHELION_APUI_TYPES_COLOR_HPP

#include <ApUI/ImGui/imgui.h>
namespace ApUI::Types
{
  struct Color
  {
    Color(float p_r = 1.0f, float p_g = 1.0f, float p_b = 1.0f, float p_a = 1.0f);
    explicit Color(ImVec4& im_color);
    explicit Color(ImColor& im_color);

    float r, g, b, a;

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color White;
    static const Color Black;
    static const Color Yellow;
    static const Color Cyan;
    static const Color Faction_TR;
    static const Color Faction_NC;
    static const Color Faction_VS;

    bool operator==(const Color &other) const;
    bool operator!=(const Color &other) const;
    inline explicit operator ImU32() const;
    inline explicit operator ImVec4() const;
  };
}

#endif //APHELION_APUI_TYPES_COLOR_HPP
