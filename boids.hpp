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

bool is_near(Boid const&, Boid const&, float);
Vector alignment(Boid const&, std::vector<Boid>, float);
Vector separation(Boid const&, std::vector<Boid>, float);
Vector cohesion(Boid const&, std::vector<Boid>, float);
 }
#endif 