#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include "SFML/Graphics.hpp"
#include <cmath>
#include <vector>

namespace bd {

const float pi = std::atan(1.f) * 4;
inline SpaceDimensions windowDimensions{900.f, 900.f};
class Boid
{
 private:
  Vector position_;
  Vector velocity_;
  bool isPredator_;

 public:
  Boid(Vector p, Vector v, bool isPred)
      : position_{p}
      , velocity_{v}
      , isPredator_{isPred}
  {}

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

  auto isPredator() const
  {
    return isPredator_;
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

  void correct_borders();

  bool hasNeighbour(Boid const&, float) const;
  void biological_limits();
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
  Parameters flock_parameters_;
  Boid predator_;

 public:
  explicit Flock(std::vector<Boid> v, Parameters p, Boid predator)
      : flock_{v}
      , flock_parameters_{p}
      , predator_{predator}
  {}

  auto setPredator(const Boid& p)
  {
    predator_ = p;
  }

  auto const& getFlock() const
  {
    return flock_;
  }

  auto const& getPredator() const
  {
    return predator_;
  }

  void evolution();
  Boid predator_evolution();
  void overlapping(Boid&);
};

} // namespace bd

#endif
