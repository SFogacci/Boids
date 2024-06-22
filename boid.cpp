#include "boid.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>

namespace bd {

bool operator==(Boid const& v, Boid const& p)
{
  if (v.getVelocity() == p.getVelocity()
      && v.getPosition() == p.getPosition()) {
    return true;
  } else {
    return false;
  };
} 

Vector generateCoordinate(float a, float b)
{
  std::random_device rd;
  std::uniform_real_distribution<> dis(a, b);
  Vector coordinates{static_cast<float>(dis(rd)), static_cast<float>(dis(rd))};
  return coordinates;
}

void Boid::correct_borders() 
{
  float consistency_factor{1.f}; //20.f
  if (position_.x > 850.f) {
    velocity_.x += consistency_factor * (-position_.x + 850.f);
  }
  if (position_.y > 850.f) {
    velocity_.y += consistency_factor * (-position_.y + 850.f);
  }
  if (position_.x < 50.f) {
    velocity_.x += consistency_factor * (-position_.x + 50.f);
  }
  if (position_.y < 50.f) {
    velocity_.y += consistency_factor * (-position_.y + 50.f);
  }
}

// void Predator::correct_borders()
// {
//   float consistency_factor{1.f}; //20.f
//   if (position_.x > 850.f) {
//     velocity_.x += consistency_factor * (-position_.x + 850.f);
//   }
//   if (position_.y > 850.f) {
//     velocity_.y += consistency_factor * (-position_.y + 850.f);
//   }
//   if (position_.x < 50.f) {
//     velocity_.x += consistency_factor * (-position_.x + 50.f);
//   }
//   if (position_.y < 50.f) {
//     velocity_.y += consistency_factor * (-position_.y + 50.f);
//   }
// }

bool Boid::isClose(Boid const& b, float d) const
{
  auto distance = norm((b.getPosition() - position_));
  return distance < d;
}

bool Boid::hasNeighbour(Boid const& b, float d) const
{
  return isClose(b, d) && (&b != this);
}

// bool Predator::isClose(Boid const& b, float d) const
// {
//   auto distance = norm((b.getPosition() - position_));
//   return distance < d;
// }

void Boid::biological_limits()
{
  float maximum_speed = 5.f; //500.f
  if (norm(velocity_) > maximum_speed) {
    velocity_ = maximum_speed * velocity_ / norm(velocity_);
  }
}

// void Predator::biological_limits()
// {
//   float maximum_speed = 10.f; //600.f
//   if (norm(velocity_) > maximum_speed) {
//     velocity_ = maximum_speed * velocity_ / norm(velocity_);
//   }
// }

void Flock::predator_evolution(Predator& p)
{
  Vector center_of_mass{};
  float d{flock_parameters_.d};
  std::vector<Boid> preys;
  std::for_each(flock_.begin(), flock_.end(),
                [p, d, &preys, &center_of_mass](Boid const& b) {
                  if (p.isClose(b, d)) {
                    center_of_mass += b.getPosition();
                    preys.push_back(b);
                  } else {
                  };
                });

  Parameters par{0.f, 0.f,         flock_parameters_.d, flock_parameters_.ds,
                 1.f, preys.size()};
  // Flock poor_preys(preys, par);

  if (preys.size() >= 1) {
    float consistency_factor{1.f}; //60.f
    Vector hunting =
        (center_of_mass / static_cast<float>(preys.size()) - p.getPosition())
        / 100.f; //No factor
    p.setPosition(p.getPosition() + hunting / consistency_factor);
    p.setVelocity(p.getVelocity() + hunting);
  } else {
    float consistency_factor{1.f}; //60.f
    p.setPosition(p.getPosition() + p.getVelocity() / consistency_factor);
  }
  p.correct_borders();
  p.biological_limits();
  // }

  // void Flock::evolution()
  // {
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
              sums.separation +=
                  flock_parameters_.ds
                  / norm(other.getPosition() - boid.getPosition())
                  / norm(other.getPosition() - boid.getPosition())
                  * (other.getPosition()
                     - boid.getPosition()); // versore e normalizzazione su ds
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
                + flock_parameters_.c * corrections.cohesion / 100.f //No factor
                - flock_parameters_.s * corrections.separation;

    if (std::find_if(preys.begin(), preys.end(),
                     [boid](Boid const& prey) { return prey == boid; })
        != preys.end()) {
      newVel = (flock_parameters_.d / norm(p.getPosition() - boid.getPosition())
                * par.s * p.getVelocity());
    }

    float consistency_factor{1.f}; // 60.f
    Boid modified_boid(boid.getPosition() + newVel / (consistency_factor),
                       newVel);
    modified_boid.correct_borders();
    std::for_each(
        flock_.begin(), flock_.end(), [&modified_boid](Boid const& bird) {
          if (bird == modified_boid) {
            modified_boid.setPosition(modified_boid.getPosition()
                                      + generateCoordinate(-1.f, 1.f));
          };
        });
    modified_boid.biological_limits();
    modified_flock.push_back(modified_boid);
  }

  flock_ = modified_flock;
}
} // namespace bd
