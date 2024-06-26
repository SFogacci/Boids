#include "vectors.hpp"
#include <cassert>
#include <cmath>
#include <random>

namespace bd {

Vector Vector::operator+=(Vector const& add)
{
  return {x += add.x, y += add.y};
}

Vector operator+(Vector const& a, Vector const& b)
{
  auto sum = a;
  return sum += b;
}

Vector operator*(float c, Vector const& v)
{
  return {c * v.x, c * v.y};
}

Vector operator*(Vector const& v, float c)
{
  return c * v;
}

Vector operator-(Vector const& a, Vector const& b)
{
  return a + (-1.f) * b;
}

Vector operator/(Vector const& v, float d)
{
  assert(d != 0); // da ottimizzare con exception ad esempio
  return 1.f / d * v;
}

bool operator==(Vector const& v, Vector const& p)
{
  return (v.x == p.x && v.y == p.y);
}

float norm(Vector const& v)
{
  return std::hypot(v.x, v.y);
}

Vector generateCoordinates(float a, float b)
{
  std::random_device rd;
  std::uniform_real_distribution<float> dis(a, b);
  Vector coordinates{dis(rd), dis(rd)};
  return coordinates;
}

void normalize(Vector& v, float f)
{
  v = f / norm(v) * v;
}
} // namespace bd