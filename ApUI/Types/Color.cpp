#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "Color.hpp"

namespace ApUI::Types
{
  const Color Color::Red        = { 1.0f, 0.0f, 0.0f };
  const Color Color::Green      = { 0.0f, 1.0f, 0.0f };
  const Color Color::Blue       = { 0.0f, 0.0f, 1.0f };
  const Color Color::White      = { 1.0f, 1.0f, 1.0f };
  const Color Color::Black      = { 0.0f, 0.0f, 0.0f };
  const Color Color::Yellow     = { 1.0f, 1.0f, 0.0f };
  const Color Color::Cyan       = { 0.0f, 1.0f, 1.0f };
  const Color Color::Faction_TR = { 242.0f, 13.0f, 29.0f };
  const Color Color::Faction_NC = { 49.0f, 57.0f, 247.0f };
  const Color Color::Faction_VS = { 140.0f, 12.0f, 197.0f };

  Color::Color(float p_r, float p_g, float p_b, float p_a)
  : r(p_r), g(p_g), b(p_b), a(p_a)
  {
  }

  Color::Color(ImVec4 &im_color)
  : Color(im_color.w, im_color.x, im_color.y, im_color.z)
  {}

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

  Color::operator ImU32 () const
  {
    return ImGui::ColorConvertFloat4ToU32(operator ImVec4());
  }

  Color::operator ImVec4() const
  {
    return ImVec4(r, g, b, a);
  }
}



#pragma clang diagnostic pop