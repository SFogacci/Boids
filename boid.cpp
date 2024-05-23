#include "boid.hpp"
#include <iostream>

namespace bd {

bool Boid::isClose(bd::Boid const& b, float d) const
{
  auto distance = norm((b.getPosition() - position_));
  return distance < d; //&& distance != 0; non considera se stesso un vicino
                       // ma potrebbe evitare un altro nello
                       // stesso posto
}

// std::vector<Boid> Flock::evolution()
void Flock::evolution()
{
  std::vector<bd::Boid> modified_flock;
  modified_flock.reserve(flock_.size());

  for (auto const& boid : flock_) {
    Vector separation{0.f, 0.f};
    Vector alignment;
    Vector cohesion;
    Vector sumVel{0.f, 0.f};
    Vector sumPos{0.f, 0.f};
    float neighbours{};
    for (auto const& other : flock_) {
      if (&other != &boid) {
        if (boid.isClose(other, flock_parameters_.d)) {
          sumPos += other.getPosition();
          sumVel += other.getVelocity();
          ++neighbours;
        }

        if (boid.isClose(other, flock_parameters_.ds)) {
          separation += other.getPosition();
        }
      }
    }
    if (neighbours != 0.f) {
      alignment = sumVel / neighbours;
      cohesion  = (sumPos / neighbours) - boid.getPosition();
    }

    Vector newVel = boid.getVelocity() + flock_parameters_.a * alignment
                  + flock_parameters_.c * cohesion
                  + -flock_parameters_.s * separation;
    // Vector newPos = boid.getPosition() + newVel;

    Boid modified_boid(boid.getPosition() + newVel, newVel);
    modified_flock.push_back(modified_boid);
  }
  flock_ = modified_flock;
}
} // namespace bd
