#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include "SFML/Graphics.hpp"
#include <cmath>
#include <vector>

namespace bd {

const float pi = std::atan(1.f) * 4;

class Flock
{
  std::vector<Boid> flock_;
  std::size_t size_{};
  Parameters flock_parameters_;

 public:
  Flock(Boid const& b, Parameters a)
      : flock_parameters_{a}
  {
    flock_.push_back(b);
    ++size_;
  };

  Flock(std::vector<Boid> b, Parameters a)
      : flock_{b}
      , flock_parameters_{a}
  {
    size_ = b.size();
  }
  // class invariant is flock_.size() == size_;

  auto const& flock() const
  {
    return flock_;
  }
  std::vector<bd::Boid> evolution()
  {}

  Vector separation(bd::Boid const&, float, float) const;

  Vector alignment(bd::Boid const&, float, float) const;

  Vector cohesion(bd::Boid const&, float, float) const;
};

class Boid
{
  Vector position_;
  Vector velocity_;

 public:
  Boid(Vector p, Vector v)
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

  auto getOrientation() const
  {
    if (velocity_.x > 0 && velocity_.y > 0) {
      std::atan((velocity_.y) / velocity_.x) * (180 / pi);
    }
    if (velocity_.x < 0 && velocity_.y < 0) {
      std::atan((velocity_.y) / velocity_.x) * (180 / pi) + 180.f;
    };
    if (velocity_.x > 0 && velocity_.y < 0) {
      std::atan((velocity_.y) / velocity_.x) * (180 / pi) + 360.f;
    };
  }

  void setPosition(Vector const& p)
  {
    position_ = p;
  }

  void setVelocity(Vector const& v)
  {
    velocity_ = v;
  }

  void setRotation(float)
  {
    if (velocity_.x > 0 && velocity_.y > 0) {
      std::atan((velocity_.y) / velocity_.x) * (180 / pi);
    }
    if (velocity_.x < 0 && velocity_.y < 0) {
      std::atan((velocity_.y) / velocity_.x) * (180 / pi) + 180.f;
    };
    if (velocity_.x > 0 && velocity_.y < 0) {
      std::atan((velocity_.y) / velocity_.x) * (180 / pi) + 360.f;
    };
  }

  bool isClose(Boid const&, float) const;

  auto moveBoid(bd::Flock const& flock, bd::Boid& b, float const d,
                float const ds, float s, float const a, float const c);

  // using Flock = std::vector<Boid>;

  // Vector separation(Flock const&, float, float) const;

  // Vector alignment(Flock const&, float, float) const;

  // Vector cohesion(Flock const&, float, float) const;
};

struct Parameters
{
  float a;
  float c;
  float s;
  float d;
  float ds;
};

} // namespace bd

#endif