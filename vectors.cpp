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

Vector operator-(Vector const& a, Vector const& b)
{
  return a + (-1.f) * b;
}

Vector operator/(Vector const& v, float d)
{
  assert(d != 0);
  return 1.f / d * v;
}

bool operator==(Vector const& a, Vector const& b)
{
  return (a.x == b.x && a.y == b.y);
}

float norm(Vector const& v)
{
  return std::hypot(v.x, v.y);
}

float generateCoordinate(float a, float b)
{
  std::random_device rd;
  std::uniform_real_distribution<float> dis(a, b);
  return dis(rd);
}

void normalize(Vector& v, float f)
{
  if (norm(v) != 0) {
    v = f / norm(v) * v;
  }
}

Vector toroidalDifference(Vector const& a, Vector const& b)
{
  float xDiff{a.x - b.x};
  if (std::abs(xDiff) > windowDimensions.x / 2.f) {
    xDiff = windowDimensions.x - std::abs(xDiff);
    xDiff *= (a.x > b.x) ? -1.f : 1.f;
  }

  float yDiff{a.y - b.y};
  if (std::abs(yDiff) > windowDimensions.y / 2.f) {
    yDiff = windowDimensions.y - std::abs(yDiff);
    yDiff *= (a.y > b.y) ? -1.f : 1.f;
  }

  return Vector{xDiff, yDiff};
}

} // namespace bd