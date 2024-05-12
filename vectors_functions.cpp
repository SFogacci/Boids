#include "boids.hpp"
#include <cmath>

namespace bd {
float distance(Boid const& a, Boid const& b)
{
  return norm(vecsum(a.getPosition(), vecmul(b.getPosition(), -1.f)));
}

Vector Boid::getPosition() const
{
  return position;
}
Vector Boid::getVelocity() const
{
  return velocity;
}

Vector operator+(Vector const& v1, Vector const& v2)
{
  Vector sum{v1.x + v2.x, v1.y + v2.y};
  return sum;
}

Vector operator-(Vector const& v1, Vector const& v2)
{
  Vector diff{v1.x - v2.x, v1.y - v2.y};
  return diff;
}

Vector operator*(float a, Vector const& v)
{
  Vector mul{a * v.x, a * v.y};
  return mul;
}

float norm(Vector a)
{
  return std::hypot(a.x, a.y);
}
} // namespace bd
