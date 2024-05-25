#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>
#include <vector>

namespace bd {

const float pi = std::atan(1.f) * 4;
class Boid
{
  Vector position_;
  Vector velocity_;
  sf::ConvexShape birdShape;

 public:
  Boid(Vector p, Vector v)
      : position_{p}
      , velocity_{v}
  {
    setShape();
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

  sf::ConvexShape getShape() const
  {
    return birdShape;
  }

  void setPosition(Vector const& p)
  {
    position_ = p;
  }

  void setVelocity(Vector const& v)
  {
    velocity_ = v;
  }

  void setx_Velocity (float const x){
    velocity_.x=x;
  }

  void sety_Velocity (float const y){
    velocity_.y=y;
  }

  bool isClose(Boid const&, float) const;

  void setShape()
  {
    birdShape.setPointCount(3);
    birdShape.setPoint(0, sf::Vector2f(position_.x - 10.f, position_.y - 5.f));
    birdShape.setPoint(1, sf::Vector2f(position_.x + 10.f, position_.y));
    birdShape.setPoint(2, sf::Vector2f(position_.x - 10.f, position_.y + 5.f));
    birdShape.setFillColor(sf::Color::Red);
    birdShape.setOutlineColor(sf::Color::White);
    birdShape.setOutlineThickness(1.f);
    birdShape.setPosition(position_.x, position_.y);
    birdShape.setOrigin(position_.x, position_.y);
    birdShape.setRotation(getOrientation());
  }
};

struct Parameters
{
  float a;
  float c;
  float d;
  float ds;
  float s;
};

class Flock
{
  std::vector<Boid> flock_;
  // std::size_t size_{};
  Parameters flock_parameters_;

 public:
  Flock(Boid const& b, Parameters a)
      : flock_parameters_{a}
  {
    flock_.push_back(b);
    //  ++size_;
  }

  Flock(std::vector<Boid> b, Parameters a)
      : flock_{b}
      , flock_parameters_{a}
  {
    // size_ = b.size();
  }
  // class invariant is flock_.size() == size_;

  auto const& flock() const
  {
    return flock_;
  }

  void evolution();
};

// void gameLoop (Flock &);

} // namespace bd

#endif