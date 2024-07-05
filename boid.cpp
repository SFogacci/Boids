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

void Boid::correctBorders() // teletrasporto toroidale
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

bool Boid::hasNeighbour(Boid const& b, float d) const
{
  auto distance = toroidalDifference(position_, b.getPosition());
  return norm(distance) < d && (&b != this);
}

void Boid::biologicalLimits()
{
  const float maximum_speed{5.f};
  if (norm(velocity_) > maximum_speed) {
    normalize(velocity_, maximum_speed);
  }
}

Boid Boid::predatorEvolution(Flock const& f) const // Tutto ciò che riguarda distanze e correzioni è stato trasposto
{                                                  // nello spazio toroidale. Le regole di correzione per l'alignment (Cami l'ho
  assert(isPredator_);
  auto copy{*this};
  const auto flock{f.getFlock()};
  const auto parameters{f.getFlockParameters()};
  const float d{2.f * parameters.d};

  const auto preys = static_cast<float>(std::count_if(flock.begin(), flock.end(), [&](auto const& boid) { return hasNeighbour(boid, d); }));
  assert(preys >= 0.f);
  if (preys != 0.f) {
    const auto center_of_mass = std::accumulate(flock.begin(), flock.end(), Vector{}, [&](auto& sum, auto const& b) {
      if (hasNeighbour(b, d)) {
        auto difference = toroidalDifference(b.getPosition(), position_); // Calcolo centro di massa
                                                                          // nello spazio toroidale.
        sum += getPosition() + difference;                                // Questo non è uguale alla posizione del boid?
        // Tutto quello qui dentro non è riassumibile in sum += b.getPosition()?
      }
      return sum;
    });
    const auto hunting        = toroidalDifference(center_of_mass / preys, position_);
    copy.setVelocity(velocity_ + hunting); // Nessun parametro?
    copy.biologicalLimits(); //dentro al caso di prede non nulle, altrimenti la velocità non varia
  }
  copy.setPosition(position_ + copy.getVelocity());
  copy.correctBorders();
  return copy;
}

void Flock::evolution(Boid const& p)
{
  assert(p.isPredator());
  std::vector<Boid> modifiedFlock;
  modifiedFlock.reserve(flock_.size());

  for (Boid const& boid : flock_) {
    Boid modifiedBoid(boid);
    if (boid.hasNeighbour(p, flockParameters_.d)) {
      const auto separation_predator = flockParameters_.s * toroidalDifference(boid.getPosition(), p.getPosition());
      modifiedBoid.setVelocity(boid.getVelocity() + flockParameters_.s * separation_predator); // così moltiplichiamo 2 volte per s
    }

    const auto neighbours = static_cast<float>(std::count_if(flock_.begin(), flock_.end(), [&](auto const& other) { return boid.hasNeighbour(other, flockParameters_.d); }));
    assert(neighbours >= 0.f);
    if (neighbours != 0.f) {
      auto corrections = std::accumulate(flock_.begin(), flock_.end(), Corrections{}, [&](auto& sums, auto const& other) {
        if (boid.hasNeighbour(other, flockParameters_.d)) {
          auto distance = toroidalDifference(other.getPosition(), boid.getPosition());
          sums.alignment += other.getVelocity();
          sums.cohesion += distance;
          if (boid.hasNeighbour(other, flockParameters_.ds)) {
            normalize(distance, flockParameters_.ds / norm(distance));
            sums.separation += distance;
          }
        }
        return sums;
      });

      corrections.alignment = corrections.alignment / neighbours - boid.getVelocity();
      corrections.cohesion  = corrections.cohesion / neighbours;

      modifiedBoid.setVelocity(modifiedBoid.getVelocity() + flockParameters_.a * corrections.alignment + flockParameters_.c * corrections.cohesion
                                - flockParameters_.s * corrections.separation); // Perché togliamo la separation e
                                                                                 // aggiungiamo le altre?
    }
    modifiedBoid.biologicalLimits(); // O qui, oppure se lo vogliamo mettere dentro if,
                                      // allora va controllato anche l'input
    modifiedBoid.setPosition(modifiedBoid.getPosition() + modifiedBoid.getVelocity());
    modifiedBoid.correctBorders();
    overlapping(modifiedFlock, modifiedBoid);
    modifiedFlock.push_back(modifiedBoid);
  }

  flock_ = modifiedFlock;
}

} // namespace bd
