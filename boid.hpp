#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

namespace bd {

const float pi = std::atan(1.f) * 4;

class Flock;

class Boid
{
 private:
  Vector position_;
  Vector velocity_{0.f, 0.f}; // value initialization not necessary
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
  Parameters flockParameters_;

 public:
  explicit Flock(std::vector<Boid> v, Parameters p)
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

inline void overlapping(std::vector<Boid>& birds, Boid& boid)
{
  std::for_each(birds.begin(), birds.end(), [&boid](Boid const& other) {
    if (other.getPosition() == boid.getPosition()) {
      boid.setPosition(boid.getPosition() + Vector{generateCoordinate(-1.f, 1.f), generateCoordinate(-1.f, 1.f)});
    }
  });
}
} // namespace bd

#endif
