#include "boids.hpp"
#include <cmath>

namespace bd {
inline Vector Boid::getPosition() const
{
  return position;
}
inline Vector Boid::getVelocity() const
{
  return velocity;
}

inline Vector vecsum(Vector const& a, Vector const& b)
{
  return {a.x + b.x, a.y + b.y};
}

inline Vector vecdif(Vector const& a, Vector const& b)
{
  return {a.x - b.x, a.y - b.y};
}

inline Vector vecmul(Vector const& a, float b)
{
  return {a.x * b, a.y * b};
}

inline float norm(Vector a)
{
  return std::hypot(a.x, a.y);
}
inline float distance(Boid const& a, Boid const& b)
{
  return norm(vecdif(a.getPosition(), b.getPosition()));
}
} // namespace bd
