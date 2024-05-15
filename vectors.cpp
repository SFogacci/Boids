#include "vectors.hpp"
#include <cassert>
#include <cmath>

namespace bd {

Vector Vector::operator+=(Vector const& b)
{
  return {this->x += b.x, this->y += b.y};
}

Vector operator+(Vector const& a, Vector const& b)
{
  auto sum = a;
  return sum += b;
}

Vector operator*(double c, Vector const& v)
{
  return {c * v.x, c * v.y};
}

Vector operator-(Vector const& a, Vector const& b)
{
  return a + (-1) * b;
}

Vector operator/(Vector const& v, double d)
{
  assert(d != 0); // da ottimizzare con exception ad esempio
  return 1. / d * v;
}

double norm(Vector const& v)
{
  return std::hypot(v.x, v.y);
}
} // namespace bd