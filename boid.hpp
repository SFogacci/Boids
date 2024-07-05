#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

namespace bd {

const float pi = std::atan(1.f) * 4;

class Flock;

class Boid
{
 private:
  Vector position_;
  Vector velocity_{0.f, 0.f};
  bool isPredator_{0};

 public:
  explicit Boid(Vector p, Vector v)
      : position_{p}
      , velocity_{v}
  {}

  Boid(Vector p, Vector v, bool isPred)
      : position_{p}
      , velocity_{v}
      , isPredator_{isPred}
  {}

  auto isPredator() const
  {
    return isPredator_;
  }

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

  Boid predator_evolution(Flock const&) const;
  void correct_borders();
  bool hasNeighbour(Boid const&, float) const;
  void biological_limits();
};

bool operator==(Boid const&, Boid const&);

struct Parameters
{
  float c;
  float a;
  float s;
  float d;
  float ds;
  int n;

  Parameters() = default;

  Parameters(float o, float p, float q, float r, float t, int u)
      : c{o}
      , a{p}
      , s{q}
      , d{r}
      , ds{t}
      , n{u}
  {}

  explicit Parameters(std::vector<float> v, int p)
      : c{v[0]}
      , a{v[1]}
      , s{v[2]}
      , d{v[3]}
      , ds{v[4]}
      , n{p}
  {}
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
  Parameters flock_parameters_;

 public:
  explicit Flock(std::vector<Boid> v, Parameters p)
      : flock_{v}
      , flock_parameters_{p}
  {}

  auto const& getFlock() const
  {
    return flock_;
  }

  auto const& getFlockParameters() const
  {
    return flock_parameters_;
  }

  void evolution(Boid const&);
};
} // namespace bd

#endif
