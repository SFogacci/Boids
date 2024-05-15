#include "boid.hpp"
namespace bd {

auto Boid::isClose(Boid const& b, double d) const
{
  auto distance = norm((b.getPosition() - this->position_));
  return distance < d; //&& distance != 0; non considera se stesso un vicino
                       // ma potrebbe evitare un altro nello
                       // stesso posto
}

Vector Boid::separation(Flock const& f, double ds, double s) const
{
  Vector correction;
  for (auto const& b : f) {
    if (this->isClose(b, ds)) {
      correction += b.getPosition() - this->position_;
    }
  }
  return -s * correction;
}

Vector Boid::alignment(Flock const& f, double d, double a) const
{
  Vector sumVel;
  int size{};
  for (auto const& b : f) {
    if (this->isClose(b, d)) {
      sumVel += b.getVelocity();
      ++size;
    }
  }
  Vector correction;
  if (size != 1) {
    correction = (sumVel - this->velocity_) / (size - 1);
  } // ho messo un assert per la divisione per 0, da migliorare
  return a * correction;
}

Vector Boid::cohesion(Flock const& f, double d, double c) const
{
  Vector sumPos;
  int size{};
  for (auto const& b : f) {
    if (this->isClose(b, d)) {
      sumPos += b.getPosition();
      ++size;
    }
  }
  Vector correction;
  if (size != 1) {
    auto cmPos = (sumPos - this->position_) / (size - 1);
    correction = cmPos - this->position_;
  } // ho messo un assert per la divisione per 0, da migliorare
  return c * correction;
}

} // namespace bd