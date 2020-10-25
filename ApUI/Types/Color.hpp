#ifndef APHELION_APUI_TYPES_COLOR_HPP
#define APHELION_APUI_TYPES_COLOR_HPP

#include <ApUI/ImGui/imgui.h>
namespace ApUI::Types
{
  struct Color
  {
    Color(float p_r = 255, float p_g = 255, float p_b = 255, float p_a = 255);
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

    [[nodiscard]] ImColor ToImColor() const;
    inline explicit operator ImColor() const;
    [[nodiscard]] ImVec4 ToImVec4() const;
    inline explicit operator ImVec4() const;
  };
}

#endif //APHELION_APUI_TYPES_COLOR_HPP
