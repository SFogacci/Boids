#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>


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
 }
#endif 