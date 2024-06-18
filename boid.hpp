#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include <cmath>
#include <vector>

namespace bd {

const float pi = std::atan(1.f) * 4;

class Boid
{
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

  // void setPosition(Vector const& p)
  // {
  //   position_ = p;
  // }

  // void setVelocity(Vector const& v)
  // {
  //   velocity_ = v;
  // }

  // void setx_Velocity(float const x)
  // {
  //   velocity_.x = x;
  // }

  // void sety_Velocity(float const y)
  // {
  //   velocity_.y = y;
  // }

  void correct_borders();

  bool isClose(Boid const&, float) const;
  bool hasNeighbour(Boid const&, float) const;
};

struct Parameters
{
  float a;
  float c;
  float d;
  float ds;
  float s;
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
  // std::size_t size_{};
  Parameters flock_parameters_;

 public:
  explicit Flock(Boid const& b, Parameters p)
      : flock_parameters_{p}
  {
    flock_.push_back(b);
    //  ++size_;
  }

  explicit Flock(std::vector<Boid> v, Parameters p)
      : flock_{v}
      , flock_parameters_{p}
  { // size_ = b.size();
  }
  // class invariant is flock_.size() == size_;

  auto const& getFlock() const
  {
    return flock_;
  }

  void evolution();
};

} // namespace bd

#endif
