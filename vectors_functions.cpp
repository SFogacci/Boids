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

Vector vecsum(Vector const& a, Vector const& b)
{
  return {a.x + b.x, a.y + b.y};
}

Vector vecdif(Vector const& a, Vector const& b)
{
  return {a.x - b.x, a.y - b.y};
} 

Vector vecmul(Vector const& a, float b)
{
  return {a.x * b, a.y * b};
}

float norm(Vector a)
{
  return std::hypot(a.x, a.y);
}
} // namespace bd
