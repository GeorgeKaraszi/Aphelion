#ifndef APHELION_APUI_TYPES_COLOR_HPP
#define APHELION_APUI_TYPES_COLOR_HPP

namespace ApUI::Types
{
  struct Color
  {
    Color(float p_r = 1.0f, float p_g = 1.0f, float p_b = 1.0f, float p_a = 1.0f);

    float r, g, b, a;

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color White;
    static const Color Black;
    static const Color Yellow;
    static const Color Cyan;

    bool operator==(const Color &other) const;
    bool operator!=(const Color &other) const;
  };
}

#endif //APHELION_APUI_TYPES_COLOR_HPP
