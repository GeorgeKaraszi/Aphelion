#include "Color.hpp"

namespace ApUI::Types
{
  const Color Color::Red        = { 255, 0, 0 };
  const Color Color::Green      = { 0, 255, 0 };
  const Color Color::Blue       = { 0, 0, 255 };
  const Color Color::White      = { 255, 255, 255 };
  const Color Color::Black      = { 0, 0, 0 };
  const Color Color::Yellow     = { 255, 255, 0 };
  const Color Color::Cyan       = { 0, 255, 255 };
  const Color Color::Faction_TR = { 242, 13, 29 };
  const Color Color::Faction_NC = { 49, 57, 247 };
  const Color Color::Faction_VS = { 140, 12, 197 };

  Color::Color(int p_r, int p_g, int p_b, int p_a)
  : r(p_r), g(p_g), b(p_b), a(p_a)
  {
  }

  Color::Color(ImVec4 &im_color)
  {
    float sc = 1 / 255.0f;
    r = (int)(im_color.w / sc);
    g = (int)(im_color.x / sc);
    b = (int)(im_color.y / sc);
    a = (int)(im_color.z / sc);
  }

  Color::Color(ImColor &im_color)
  : Color(im_color.Value)
  {}

  bool Color::operator==(const Color &other) const
  {
    return this->r == other.r &&
    this->g == other.g &&
    this->b == other.b &&
    this->a == other.a;
  }

  bool Color::operator!=(const Color &other) const
  {
    return !operator==(other);
  }

  ImColor Color::ToImColor() const
  {
    return ImColor(r, g, b, a);
  }

  Color::operator ImColor() const
  {
    return ToImColor();
  }

  ImVec4 Color::ToImVec4() const
  {
    return ToImColor().Value;
  }

  Color::operator ImVec4() const
  {
    return ToImVec4();
  }
}
