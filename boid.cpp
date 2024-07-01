#include "boid.hpp"
#include "vectors.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

namespace bd {

const float dt{1.f};

bool operator==(Boid const& a, Boid const& b)
{
  return (a.getVelocity() == b.getVelocity()
          && a.getPosition() == b.getPosition());
}

void Boid::correct_borders() // teletrasporto toroidale
{
  if (position_.x > w_window) {
    position_.x -= w_window;
  } else if (position_.x < 0.f) {
    position_.x += w_window;
  }
  if (position_.y > h_window) {
    position_.y -= h_window;
  } else if (position_.y < 0.f) {
    position_.y += h_window;
  }
}

bool Boid::hasNeighbour(Boid const& b, float d)
    const // Al posto della distanza normale, usa distanza toroidale.
{
  // float xDist   = toroidalDistance(position_.x, b.getPosition().x, 900.f);
  // float yDist   = toroidalDistance(position_.y, b.getPosition().y, 900.f);
  // auto distance = std::hypot(xDist, yDist);
  auto distance =
      toroidalDifference(position_, b.getPosition(), windowDimensions);
  return norm(distance) < d && (&b != this);
}

void Boid::biological_limits()
{
  const float maximum_speed = 5.f;
  if (norm(velocity_) > maximum_speed) {
    normalize(velocity_, maximum_speed);
  }
}

Predator Flock::predator_evolution(Predator const& p)
    const // Tutto ciò che riguarda distanze e correzioni è stato trasposto
{ // nello spazio toroidale. Le regole di correzione per l'alignment (Cami l'ho
  // scritto bene solo per te)
  Predator copy = p; // non sono state modificate.
  const float d = 2.f * flock_parameters_.d;

  const auto preys = static_cast<float>(
      std::count_if(flock_.begin(), flock_.end(),
                    [&](auto const& boid) { return p.hasNeighbour(boid, d); }));
  assert(preys >= 0.f);
  if (preys != 0.f) {
    const auto center_of_mass = std::accumulate(
        flock_.begin(), flock_.end(), Vector{}, [&](auto& sum, auto const& b) {
          if (p.hasNeighbour(b, d)) {
            // sum += b.getPosition();
            auto difference =
                toroidalDifference(b.getPosition(), p.getPosition(),
                                   windowDimensions); // Calcolo centro di massa
                                                      // nello spazio toroidale.
            sum += p.getPosition() + difference;
          }
          return sum;
        });
    const auto hunting = toroidalDifference(center_of_mass / preys,
                                            p.getPosition(), windowDimensions);
    copy.setVelocity(p.getVelocity() + hunting);
    copy.biological_limits();
  }
  copy.setPosition(copy.getPosition() + dt * copy.getVelocity());
  copy.correct_borders();
  return copy;
}

void Flock::evolution(Predator const& p)
{
  std::vector<Boid> modified_flock;
  modified_flock.reserve(flock_.size());

  for (Boid const& boid : flock_) {
    Boid modified_boid(boid);
    if (boid.hasNeighbour(p, flock_parameters_.d)) {
      const auto separation_predator =
          flock_parameters_.s
          * (flock_parameters_.d
             / norm(toroidalDifference(p.getPosition(), boid.getPosition(),
                                    windowDimensions))
             * p.getVelocity());
      modified_boid.setVelocity(boid.getVelocity() + separation_predator);
    }

    const auto neighbours = static_cast<float>(
        std::count_if(flock_.begin(), flock_.end(), [&](auto const& other) {
          return boid.hasNeighbour(other, flock_parameters_.d);
        }));
    assert(neighbours >= 0.f);
    if (neighbours != 0.f) {
      auto corrections = std::accumulate(
          flock_.begin(), flock_.end(), Corrections{},
          [&](auto& sums, auto const& other) {
            if (boid.hasNeighbour(other, flock_parameters_.d)) {
              sums.alignment += other.getVelocity();
              sums.cohesion += toroidalDifference(
                  other.getPosition(), boid.getPosition(), windowDimensions);
              if (boid.hasNeighbour(other, flock_parameters_.ds)) {
                auto distance = toroidalDifference(
                    other.getPosition(), boid.getPosition(), windowDimensions);
                normalize(distance, flock_parameters_.ds / norm(distance));
                sums.separation += distance;
              }
            }
            return sums;
          });

      corrections.alignment =
          corrections.alignment / neighbours - boid.getVelocity();
      corrections.cohesion = corrections.cohesion / neighbours;

      modified_boid.setVelocity(modified_boid.getVelocity()
                                + flock_parameters_.a * corrections.alignment
                                + flock_parameters_.c * corrections.cohesion
                                - flock_parameters_.s * corrections.separation);
      modified_boid.biological_limits();
    }
    modified_boid.setPosition(modified_boid.getPosition()
                              + dt * modified_boid.getVelocity());
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
      boid.setPosition(boid.getPosition() + generateCoordinates(-1.f, 1.f));
    }
  });
}

} // namespace bd
