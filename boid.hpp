#ifndef BOID_HPP
#define BOID_HPP

#include "vectors.hpp"
#include "SFML/Graphics.hpp"
#include <cmath>
#include <vector>

namespace bd {

const float pi      = std::atan(1.f) * 4;
const auto w_window = 900; // sf::VideoMode::getDesktopMode().width;
const auto h_window =
    900; // sf::VideoMode::getDesktopMode().height; prima di inserire questi, va
         // modificata la generazione delle posizioni (h è diverso da w)

class Flock;

class Boid
{
 private:
  Vector position_;
  Vector velocity_;
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
  // Boid() = default;

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

  auto isPredator() const
  {
    return isPredator_;
  }

  Boid predator_evolution(Flock const&) const;

  void correct_borders();

  bool hasNeighbour(Boid const&, float) const;

  void biological_limits();
};

/*class Predator : public Boid // predator derivata da boid.
{
 public:
  explicit Predator(Vector position, Vector velocity)
      : Boid{position, velocity}
  {}

  Predator evolution(Flock const&) const;
};*/

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

  auto const& getFlockParameters() const
  {
    return flock_parameters_;
  }

  void evolution(Boid const&);
  // Predator predator_evolution(Predator const&) const;
  void overlapping(Boid&);
};

} // namespace bd

#endif
