#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include <algorithm>
#include <vector>

namespace bd {

class Flock;

class Boid
{
 private:
  Vector position_;
  Vector velocity_{};
  bool isPredator_{0};

 public:
  explicit Boid(Vector const& p, Vector const& v)
      : position_{p}
      , velocity_{v}
  {}

  explicit Boid(Vector const& p, Vector const& v, bool isPred)
      : position_{p}
      , velocity_{v}
      , isPredator_{isPred}
  {}

  auto isPredator() const
  {
    return isPredator_;
  }

  auto const& getPosition() const
  {
    return position_;
  }

  auto const& getVelocity() const
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

  Boid predatorEvolution(Flock const&) const;
  void correctBorders();
  bool hasNeighbour(Boid const&, float) const;
  void biologicalLimits();
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

  explicit Parameters(float C, float A, float S, float D, float Ds, int N)
      : c{C}
      , a{A}
      , s{S}
      , d{D}
      , ds{Ds}
      , n{N}
  {}

  explicit Parameters(std::vector<float> const& v, int p)
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

void overlapping(std::vector<Boid>& birds);

class Flock
{
  std::vector<Boid> flock_;
  Parameters flockParameters_;

 public:
  explicit Flock(std::vector<Boid> const& v, Parameters const& p)
      : flock_{v}
      , flockParameters_{p}
  {}

  auto const& getFlock() const
  {
    return flock_;
  }

  auto const& getFlockParameters() const
  {
    return flockParameters_;
  }

  void evolution(Boid const&);
};
} // namespace bd

#endif
