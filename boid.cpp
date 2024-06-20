#include "boid.hpp"
#include <algorithm>
#include <numeric>

namespace bd {

bool Boid::isClose(Boid const& b, float d) const
{
  auto distance = norm((b.getPosition() - position_));
  return distance < d;
}

bool Boid::hasNeighbour(Boid const& b, float d) const
{
  return isClose(b, d) && (&b != this);
}

void Boid::correct_borders()
{
  if (position_.x > 850.f) {
    velocity_.x += 850.f - position_.x;
  }
  if (position_.y > 850.f) {
    velocity_.y += 850.f - position_.y;
  }
  if (position_.x < 50.f) {
    velocity_.y += 50.f - position_.x;
  }
  if (position_.y < 50.f) {
    velocity_.y += 50.f - position_.y;
  }
}
/*
void Flock::evolution()
{
  std::vector<Boid> modified_flock;
  modified_flock.reserve(flock_.size());

  for (Boid const& boid : flock_) {
    auto neighbours = static_cast<float>(
        std::count_if(flock_.begin(), flock_.end(), [&](auto const& other) {
          return boid.hasNeighbour(other, flock_parameters_.d);
        })); // why does it have a long int return type?

    auto corrections = std::accumulate(
        flock_.begin(), flock_.end(), Corrections{},
        [&](auto& sums, auto const& other) {
          if (boid.hasNeighbour(other, flock_parameters_.d)) {
            sums.alignment += other.getVelocity();
            sums.cohesion += other.getPosition();
            if (boid.hasNeighbour(other, flock_parameters_.ds)) {
              sums.separation += other.getPosition() - boid.getPosition();
            }
          }
          return sums;
        });

    if (neighbours != 0.f) {
      corrections.alignment =
          corrections.alignment / neighbours - boid.getVelocity();
      corrections.cohesion =
          corrections.cohesion / neighbours - boid.getPosition();
    }

    auto newVel = boid.getVelocity()
                + flock_parameters_.a * corrections.alignment
                + flock_parameters_.c * corrections.cohesion
                - flock_parameters_.s * corrections.separation;

    Boid modified_boid(boid.getPosition() + newVel, newVel);
    modified_boid.correct_borders();
    modified_flock.push_back(modified_boid);
  }

  flock_ = modified_flock;
}*/
} // namespace bd
