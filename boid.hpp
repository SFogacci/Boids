#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include <vector>

namespace bd {

class Boid
{
  Vector position_;
  Vector velocity_;

 public:
  Boid(Vector p, Vector v)
      : position_{p}
      , velocity_{v}
  { // controlli sui valori di p e v?
  }

  auto getPosition() const
  {
    return position_;
  }

  auto getVelocity() const
  {
    return velocity_;
  }

  void setPosition(Vector const& p)
  {
    (this->position_) = p;
  }

  void setVelocity(Vector const& v)
  {
    (this->velocity_) = v;
  }

  auto isClose(Boid const&, double) const;

  using Flock = std::vector<Boid>;

  Vector separation(Flock const&, double, double) const;

  Vector alignment(Flock const&, double, double) const;

  Vector cohesion(Flock const&, double, double) const;
};

} // namespace bd

#endif