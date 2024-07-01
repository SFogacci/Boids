#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include "SFML/Graphics.hpp"
#include <cmath>
#include <vector>

namespace bd {

const float pi      = std::atan(1.f) * 4;
const auto w_window = 900.f; // sf::VideoMode::getDesktopMode().width;
const auto h_window = 900.f; // sf::VideoMode::getDesktopMode().height; prima di
                             // inserire questi, va modificata la generazione
                             // delle posizioni (h è diverso da w)
const SpaceDimensions windowDimensions{w_window, h_window};

class Boid
{
 private:
  Vector position_;
  Vector velocity_;

 public:
  Boid() = default;
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

  void correct_borders();

  // bool isClose(Boid const&, float) const;
  bool hasNeighbour(Boid const&, float) const;
  void biological_limits();
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

  Parameters()= default;

  explicit Parameters(std::vector<float> v, std::size_t p)
      : a{v[0]}
      , c{v[1]}
      , d{v[2]}
      , ds{v[3]}
      , s{v[4]}
      , n{p}
  {}

};

struct Corrections
{
  Vector alignment;
  Vector cohesion;
  Vector separation;
  Vector separation_predator;
};

class Flock
{
  std::vector<Boid> flock_;
  Parameters flock_parameters_;

 public:
  // explicit Flock(Boid const& b, Parameters p)
  //     : flock_parameters_{p}
  // {
  //   flock_.push_back(b);
  // }
  // Flock() = default; //default constructor (?)

  explicit Flock(std::vector<Boid> v, Parameters p)
      : flock_{v}
      , flock_parameters_{p}
  {}

  auto const& getFlock() const
  {
    return flock_;
  }

  void evolution(Predator const&);
  Predator predator_evolution(Predator const&) const;
  void overlapping(Boid&);
};

} // namespace bd

#endif
