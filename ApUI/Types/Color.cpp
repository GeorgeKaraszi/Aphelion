#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include "Color.hpp"

namespace ApUI::Types
{
  const Color Color::Red    = { 1.0f, 0.0f, 0.0f };
  const Color Color::Green  = { 0.0f, 1.0f, 0.0f };
  const Color Color::Blue   = { 0.0f, 0.0f, 1.0f };
  const Color Color::White  = { 1.0f, 1.0f, 1.0f };
  const Color Color::Black  = { 0.0f, 0.0f, 0.0f };
  const Color Color::Yellow = { 1.0f, 1.0f, 0.0f };
  const Color Color::Cyan   = { 0.0f, 1.0f, 1.0f };

  Color::Color(float p_r, float p_g, float p_b, float p_a)
  : r(p_r), g(p_g), b(p_b), a(p_a)
  {
  }

  bool Color::operator==(const Color &other) const
  {
    return
    this->r == other.r &&
    this->g == other.g &&
    this->b == other.b &&
    this->a == other.a;
  }

  bool Color::operator!=(const Color &other) const
  {
    return !operator==(other);
  }
}



#pragma clang diagnostic pop