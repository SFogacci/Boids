#include "boid.hpp"
#include "vectors.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>

namespace bd {

const float dt{1.f}; // il vecchio consistency factor

bool operator==(Boid const& a, Boid const& b)
{
  return (a.getVelocity() == b.getVelocity()
          && a.getPosition() == b.getPosition());
}

void Boid::correct_borders()
{
  if (position_.x > static_cast<float>(w_window)) {
    position_.x -= static_cast<float>(w_window);
  } else if (position_.x < 0.f) {
    position_.x += static_cast<float>(w_window);
  }
  if (position_.y > static_cast<float>(h_window)) {
    position_.y -= static_cast<float>(h_window);
  }
  if (position_.y < 0.f) {
    position_.y += static_cast<float>(h_window);
  } // c'è un problema sulla y per colpa della barra in alto che copre (forse?)
}

bool Boid::hasNeighbour(Boid const& b, float d) const
{
  auto distance = norm(b.getPosition() - position_);
  return distance < d && (&b != this);
}

void Boid::biological_limits()
{
  const float maximum_speed = 5.f; // 500.f
  if (norm(velocity_) > maximum_speed) {
    normalize(velocity_, maximum_speed);
  }
}

// void Predator::biological_limits()
// {
//   float maximum_speed = 10.f; //600.f
//   if (norm(velocity_) > maximum_speed) {
//     velocity_ = maximum_speed * velocity_ / norm(velocity_);
//   }
// }

Predator Flock::predator_evolution(Predator const& p) const
{
  Predator copy = p;
  const float d = 2.f * flock_parameters_.d;
  // gli do 2 volte la visione dei boid, così vede più lontano (se è un
  // predatore si sarà evoluto in modo da vedere meglio le prede, no?)

  const auto preys = static_cast<float>(
      std::count_if(flock_.begin(), flock_.end(),
                    [&](auto const& boid) { return p.hasNeighbour(boid, d); }));
  assert(preys >= 0.f);
  if (preys != 0.f) {
    const auto center_of_mass = std::accumulate(
        flock_.begin(), flock_.end(), Vector{}, [&](auto& sum, auto const& b) {
          if (p.hasNeighbour(b, d)) {
            sum += b.getPosition();
          }
          return sum;
        });
    const auto hunting = center_of_mass / preys - p.getPosition();
    copy.setVelocity(p.getVelocity() + hunting);
  }
  copy.setPosition(copy.getPosition() + dt * copy.getVelocity());
  // overlapping(copy); ??
  copy.biological_limits();
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
          * (flock_parameters_.d / norm(p.getPosition() - boid.getPosition())
             * p.getVelocity());
      modified_boid.setVelocity(boid.getVelocity() + separation_predator);
    } // l'obiettivo è farlo funzionare come separation, al momento lo
    // lascio così (così i boid tendono ad allinearsi al predatore, è quello che
    // vogliamo?)

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
              sums.cohesion += other.getPosition();
              if (boid.hasNeighbour(other, flock_parameters_.ds)) {
                auto distance = other.getPosition() - boid.getPosition();
                normalize(distance, flock_parameters_.ds / norm(distance));
                // std::cout << " distance = "
                //           << std::hypot(distance.x, distance.y) << '\n';
                sums.separation += distance; // versore e normalizzazione su ds
              }
            }
            return sums;
          });

      corrections.alignment =
          corrections.alignment / neighbours - boid.getVelocity();
      corrections.cohesion =
          corrections.cohesion / neighbours - boid.getPosition();

      modified_boid.setVelocity(
          modified_boid.getVelocity()
          + flock_parameters_.a * corrections.alignment
          + flock_parameters_.c * corrections.cohesion // /100.F (No factor)
          - flock_parameters_.s * corrections.separation);
    }
    modified_boid.setPosition(modified_boid.getPosition()
                              + dt * modified_boid.getVelocity());
    overlapping(modified_boid); // io la ho messa membro di flock, si potrebbe
                                // anche mettere membro di Boid però anziche
                                // passare un boid dovrei passare il flock

    modified_boid.biological_limits();
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
    };
  });
}
} // namespace bd
