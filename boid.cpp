#include "boid.hpp"
#include <iostream>

namespace bd {

bool Boid::isClose(bd::Boid const& b, float d) const
{
  auto distance = norm((b.getPosition() - position_));
  return distance < d;
}

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

          if (boid.isClose(other, flock_parameters_.ds)) {
            separation = separation + other.getPosition() - boid.getPosition();
          }
        }
      }
    }
    if (neighbours != 0.f) {
      alignment = sumVel / neighbours - boid.getVelocity();
      std::cout << alignment.x << '\n'; 
      cohesion  = (sumPos / neighbours)
               - boid.getPosition(); // Accelerano tra di loro non importa
                                     // quanta distanza c'è 101-102, 100-103
                                     // finiscono in 101.5
    }

    Vector newVel = boid.getVelocity() + flock_parameters_.a * alignment
                  + flock_parameters_.c * cohesion
                  - flock_parameters_.s * separation;

    Boid modified_boid(
        boid.getPosition() + newVel,
        newVel); // se vogliamo un parametro tocca accordarci (per i test)

    if (modified_boid.getPosition().x > 850.f) {
      modified_boid.setx_Velocity(newVel.x
                                  - (modified_boid.getPosition().x - 850.f));
    }
    if (modified_boid.getPosition().y > 850.f) {
      modified_boid.sety_Velocity(newVel.y
                                  - (modified_boid.getPosition().y - 850.f));
    }
    if (modified_boid.getPosition().x < 50.f) {
      modified_boid.setx_Velocity(newVel.x
                                  + (-modified_boid.getPosition().x + 50.f));
    }
    if (modified_boid.getPosition().y < 50.f) {
      modified_boid.sety_Velocity(newVel.y
                                  + (-modified_boid.getPosition().y + 50.f));
    }

    modified_flock.push_back(modified_boid);
  }
  flock_ = modified_flock;
}
} // namespace bd
