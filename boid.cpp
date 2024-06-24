#include "boid.hpp"
#include "vectors.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

namespace bd {

bool operator==(Boid const& a, Boid const& b)
{
  return (a.getVelocity() == b.getVelocity()
          && a.getPosition() == b.getPosition());
}

void Boid::correctBorders()
{
  if (position_.x > 900.f) {
    position_.x -= 900.f;
  } else if (position_.x < 0.f) {
    position_.x += 900.f;
  }
  if (position_.y > 900.f) {
    position_.y -= 900.f;
  } else if (position_.y < 0.f) {
    position_.y += 900.f;
  } // c'è un problema sulla y per colpa della barra in alto che copre (forse?)
}

bool Boid::hasNeighbour(Boid const& b, float d) const
{
  auto distance = norm(b.getPosition() - position_);
  return distance < d && (&b != this);
}

// bool Predator::isClose(Boid const& b, float d) const
// {
//   auto distance = norm((b.getPosition() - position_));
//   return distance < d;
// }

void Boid::biologicalLimits()
{
  float maximum_speed = 5.f; // 500.f
  if (norm(velocity_) > maximum_speed) {
    normalize(velocity_, maximum_speed);
  }
}

// void Predator::biologicalLimits()
// {
//   float maximum_speed = 10.f; //600.f
//   if (norm(velocity_) > maximum_speed) {
//     velocity_ = maximum_speed * velocity_ / norm(velocity_);
//   }
// }

/*void Flock::predator_evolution(Predator& p)
{
  Vector center_of_mass{};
  const float d = flock_pars_.d;
  std::vector<Boid> preys;
  std::for_each(flock_.begin(), flock_.end(),
                [p, d, &preys, &center_of_mass](Boid const& b) {
                  if (p.hasNeighbour(b, d)) {
                    center_of_mass += b.getPosition();
                    preys.push_back(b);
                  };
                });

  Parameters par{0.f, 0.f,         flock_pars_.d, flock_pars_.ds,
                 1.f, preys.size()};
  // Flock poor_preys(preys, par);

  if (preys.size() >= 1) {
    float consistency_factor{1.f}; // 60.f
    Vector hunting =
        (center_of_mass / static_cast<float>(preys.size()) - p.getPosition())
        / 100.f; // No factor
    p.setPosition(p.getPosition() + hunting / consistency_factor);
    p.setVelocity(p.getVelocity() + hunting);
  } else {
    float consistency_factor{1.f}; // 60.f
    p.setPosition(p.getPosition() + p.getVelocity() / consistency_factor);
  }
  p.correct_borders();
  p.biologicalLimits();
}*/

void Flock::evolution()
{
  std::vector<Boid> modified_flock;
  modified_flock.reserve(flock_.size());

  for (Boid const& boid : flock_) {
    const auto neighbours = static_cast<float>(
        std::count_if(flock_.begin(), flock_.end(), [&](auto const& other) {
          return boid.hasNeighbour(other, flock_pars_.d);
        }));

    if (neighbours != 0.f) {
      auto corrections = std::accumulate(
          flock_.begin(), flock_.end(), Corrections{},
          [&](auto& sums, auto const& other) {
            if (boid.hasNeighbour(other, flock_pars_.d)) {
              sums.alignment += other.getVelocity();
              sums.cohesion += other.getPosition();
              if (boid.hasNeighbour(other, flock_pars_.ds)) {
                auto distance = other.getPosition() - boid.getPosition();
                normalize(distance, flock_pars_.ds / norm(distance));
                sums.separation += distance; // versore e normalizzazione su ds
              }
            }
            return sums;
          });

      corrections.alignment =
          corrections.alignment / neighbours - boid.getVelocity();
      corrections.cohesion =
          corrections.cohesion / neighbours - boid.getPosition();

      auto newVel =
          boid.getVelocity() + flock_pars_.a * corrections.alignment
          + flock_pars_.c * corrections.cohesion // /100.F (No factor)
          - flock_pars_.s * corrections.separation;

      float consistency_factor{1.f}; // 60.f
      Boid modified_boid(boid.getPosition() + newVel / (consistency_factor),
                         newVel);

      // if (std::find_if(preys.begin(), preys.end(),
      //                  [boid](Boid const& prey) { return prey == boid; })
      //     != preys.end()) {
      //   newVel = (flock_pars_.d / norm(p.getPosition() -
      //   boid.getPosition())
      //             * par.s * p.getVelocity());
      // }

      std::for_each(
          flock_.begin(), flock_.end(), [&modified_boid](Boid const& other) {
            if (other == modified_boid) {
              modified_boid.setPosition(modified_boid.getPosition()
                                        + generateCoordinates(-1.f, 1.f));
            };
          });
      modified_boid.biologicalLimits();
      modified_boid.correctBorders();
      modified_flock.push_back(modified_boid);
    } else {
      float consistency_factor{1.f}; // 60.f
      Boid modified_boid(boid.getPosition()
                             + boid.getVelocity() / (consistency_factor),
                         boid.getVelocity());
      modified_flock.push_back(modified_boid);
    }
  }

  flock_ = modified_flock;
}
} // namespace bd
