#include "boids.hpp"
#include <cmath>

namespace bd {
float distance(Boid const& a, Boid const& b)
{
  return norm(vecdif(a.getPosition(), b.getPosition()));
}

Vector Boid::getPosition() const
{
  return position;
}
Vector Boid::getVelocity() const
{
  return velocity;
}

// Ora è primo-secondo
Vector vecdif(Vector const& a, Vector const& b)
{
  return {a.x - b.x, a.y - b.y};
}

float norm(Vector a)
{
  return std::hypot(a.x, a.y);
}
} // namespace bd