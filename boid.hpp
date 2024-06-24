#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include <cmath>
#include <vector>

namespace bd {

const float pi = std::atan(1.f) * 4;

class Boid
{
 private:
  Vector position_;
  Vector velocity_;

 public:
  explicit Boid(Vector p, Vector v)
      : position_{p}
      , velocity_{v}
  {}

  auto getPosition() const
  {
    return position_;
  }

  auto getVelocity() const
  {
    return velocity_;
  }

  float getOrientation() const
  {
    float orientation = atan2f(velocity_.y, velocity_.x) * 180.f / pi;
    if (orientation >= 0.f) {
      return orientation;
    } else {
      return orientation + 360.f;
    }
  }

  void setPosition(Vector const& p)
  {
    position_ = p;
  }

  void setVelocity(Vector const& v)
  {
    velocity_ = v;
  }

  void correctBorders();

  // bool isClose(Boid const&, float) const;
  bool hasNeighbour(Boid const&, float) const;
  void biologicalLimits();
};

class Predator : public Boid // predator derivata da boid.
{
 public:
  explicit Predator(Vector position, Vector velocity)
      : Boid{position, velocity}
  {}
};

bool operator==(Boid const&, Boid const&);

struct Parameters
{
  float a;
  float c;
  float d;
  float ds;
  float s;
  std::size_t n;
};

struct Corrections
{
  Vector alignment;
  Vector cohesion;
  Vector separation;
};

class Flock
{
  std::vector<Boid> flock_;
  Parameters flock_pars_;

 public:
  explicit Flock(Boid const& b, Parameters p)
      : flock_pars_{p}
  {
    flock_.push_back(b);
  }

  explicit Flock(std::vector<Boid> v, Parameters p)
      : flock_{v}
      , flock_pars_{p}
  {}

  auto const& getFlock() const
  {
    return flock_;
  }

  void evolution();
  void predator_evolution(Predator& p); // forse meglio come metodo di Predator?
};

} // namespace bd

#endif
