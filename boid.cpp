#include "boid.hpp"
#include "vectors.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

namespace bd {

bool operator==(Boid const& a, Boid const& b)
{
  return (a.getVelocity() == b.getVelocity() && a.getPosition() == b.getPosition());
}

void Boid::correct_borders() // teletrasporto toroidale
{
  if (position_.x > windowDimensions.x) {
    position_.x -= windowDimensions.x;
  } else if (position_.x < 0.f) {
    position_.x += windowDimensions.x;
  }
  if (position_.y > windowDimensions.y) {
    position_.y -= windowDimensions.y;
  } else if (position_.y < 0.f) {
    position_.y += windowDimensions.y;
  }
}

bool Boid::hasNeighbour(Boid const& b, float d) const // Al posto della distanza normale, usa distanza toroidale.
{
  auto distance = toroidalDifference(position_, b.getPosition());
  return norm(distance) < d && (&b != this);
}

void Boid::biological_limits()
{
  const float maximum_speed = 5.f;
  if (norm(velocity_) > maximum_speed) {
    normalize(velocity_, maximum_speed);
  }
}

Boid Boid::predator_evolution(Flock const& f) const // Tutto ciò che riguarda distanze e correzioni è stato trasposto
{                                                   // nello spazio toroidale. Le regole di correzione per l'alignment (Cami l'ho
  // scritto bene solo per te)
  assert(isPredator_);
  auto copy{*this}; // non sono state modificate.
  const auto flock{f.getFlock()};
  const auto parameters{f.getFlockParameters()};
  const float d = 2.f * parameters.d;

  const auto preys = static_cast<float>(std::count_if(flock.begin(), flock.end(), [&](auto const& boid) { return hasNeighbour(boid, d); }));
  assert(preys >= 0.f);
  if (preys != 0.f) {
    const auto center_of_mass = std::accumulate(flock.begin(), flock.end(), Vector{}, [&](auto& sum, auto const& b) {
      if (hasNeighbour(b, d)) {
        auto difference = toroidalDifference(b.getPosition(), position_); // Calcolo centro di massa
                                                                          // nello spazio toroidale.
        sum += getPosition() + difference;
      }
      return sum;
    });
    const auto hunting        = toroidalDifference(center_of_mass / preys, position_);
    copy.setVelocity(velocity_ + hunting);
    copy.biological_limits();
  }
  copy.setPosition(position_ + copy.getVelocity());
  copy.correct_borders();
  return copy;
}

void Flock::evolution(Boid const& p)
{
  assert(p.isPredator());
  std::vector<Boid> modified_flock;
  modified_flock.reserve(flock_.size());

  for (Boid const& boid : flock_) {
    Boid modified_boid(boid);
    if (boid.hasNeighbour(p, flock_parameters_.d)) {
      auto predator_distance = toroidalDifference(boid.getPosition(), p.getPosition());
      normalize(predator_distance, flock_parameters_.d / norm(predator_distance));
      modified_boid.setVelocity(boid.getVelocity() + flock_parameters_.s * predator_distance);
      // const auto separation_predator = flock_parameters_.s * toroidalDifference(boid.getPosition(), p.getPosition());
      // modified_boid.setVelocity(boid.getVelocity() + flock_parameters_.s *separation_predator);
    }

    const auto neighbours = static_cast<float>(std::count_if(flock_.begin(), flock_.end(), [&](auto const& other) { return boid.hasNeighbour(other, flock_parameters_.d); }));
    assert(neighbours >= 0.f);
    if (neighbours != 0.f) {
      auto corrections = std::accumulate(flock_.begin(), flock_.end(), Corrections{}, [&](auto& sums, auto const& other) {
        if (boid.hasNeighbour(other, flock_parameters_.d)) {
          auto distance = toroidalDifference(other.getPosition(), boid.getPosition());
          sums.alignment += other.getVelocity();
          sums.cohesion += distance;
          if (boid.hasNeighbour(other, flock_parameters_.ds)) {
            normalize(distance, flock_parameters_.ds / norm(distance));
            sums.separation += flock_parameters_.s * distance;
            // sums.separation += distance;  // implementando regola originaria per la separation si baca
          }
        }
        return sums;
      });

      corrections.alignment = corrections.alignment / neighbours - boid.getVelocity();
      corrections.cohesion  = corrections.cohesion / neighbours;

      modified_boid.setVelocity(modified_boid.getVelocity() + flock_parameters_.a * corrections.alignment + flock_parameters_.c * corrections.cohesion
                                - flock_parameters_.s * corrections.separation);
      modified_boid.biological_limits();
    }
    modified_boid.setPosition(modified_boid.getPosition() + modified_boid.getVelocity());
    overlapping(modified_boid);
    modified_boid.correct_borders();
    modified_flock.push_back(modified_boid);
  }

  flock_ = modified_flock;
}

void Flock::overlapping(Boid& boid)
{
  std::for_each(flock_.begin(), flock_.end(), [&boid](Boid const& other) {
    if (other == boid) {
      boid.setPosition(boid.getPosition() + Vector{generateCoordinates(-1.f, 1.f), generateCoordinates(-1.f, 1.f)});
    }
  });
}

} // namespace bd
