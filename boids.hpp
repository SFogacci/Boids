#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>
#include <vector>

namespace bd {

struct Vector
{
  float x{};
  float y{};
};

class Boid
{
  Vector position;
  Vector velocity;

 public:
  Boid(Vector const& p, Vector const& v)
      : position{p}
      , velocity{v}
  {}

  Vector getPosition() const;
  void setPosition();

  Vector getVelocity() const;
  void setVelocity();
};

float distance(Boid const&, Boid const&);

} // namespace bd
#endif
