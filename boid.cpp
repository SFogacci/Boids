#include "boid.hpp"
#include "vectors.hpp"
#include <algorithm>
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
  } // c'è un problema sulla y per colpa della barra in alto che copre
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
  Vector center_of_mass{};
  const float d = 2.f * flock_parameters_.d; // gli do 2 volte la visione dei boid, così vede più lontano (se è un predatore si sarà evoluto in modo da vedere meglio le prede, no?)
  std::vector<Boid> preys;

  std::for_each(flock_.begin(), flock_.end(), [p, d, &preys, &center_of_mass](Boid const& b) {
    if (p.hasNeighbour(b, d)) { // si potrebbe usare anche copy anzichè p, ma dato che non è modifictao non da problemi
      center_of_mass += b.getPosition();
      preys.push_back(b);
    };
  });

  // Parameters par{0.f, 0.f, flock_parameters_.d, flock_parameters_.ds, 1.f, preys.size()};
  if (preys.size() > 0) {
    Vector hunting = (center_of_mass / static_cast<float>(preys.size()) - p.getPosition()) / 100.f;
    copy.setVelocity(p.getVelocity() + hunting);
    copy.biological_limits();

    copy.setPosition(p.getPosition() + p.getVelocity() / dt); // così è anche già aggiunto hunting e inoltre aggiungiamo anche la velcoità del predatore, cosa che prima non avveniva

  } else {
    copy.setPosition(p.getPosition() + p.getVelocity() / dt);
  }
  copy.correct_borders();

  return copy;
}

void Flock::evolution(Predator const& p)
{
std::vector<Boid> modified_flock;
  modified_flock.reserve(flock_.size());

  for (Boid const& boid : flock_) {
    const auto neighbours = static_cast<float>(std::count_if(flock_.begin(), flock_.end(), [&](auto const& other) { return boid.hasNeighbour(other, flock_parameters_.d); }));
    Corrections corrections;
    if (neighbours != 0.f) {
      corrections = std::accumulate(flock_.begin(), flock_.end(), Corrections{}, [&](auto& sums, auto const& other) {
        if (boid.hasNeighbour(other, flock_parameters_.d)) {
          sums.alignment += other.getVelocity();
          sums.cohesion += other.getPosition();
          if (boid.hasNeighbour(other, flock_parameters_.ds)) {
            auto distance = other.getPosition() - boid.getPosition();
            normalize(distance, flock_parameters_.ds / norm(distance));
            std::cout << " distance = " << std::hypot(distance.x, distance.y) << '\n';
            sums.separation += distance; // versore e normalizzazione su ds
          }
        }
        return sums;
      });

      corrections.alignment = corrections.alignment / neighbours - boid.getVelocity();
      corrections.cohesion  = corrections.cohesion / neighbours - boid.getPosition();

      if (p.hasNeighbour(boid, flock_parameters_.d)) {
        corrections.separation_predator += (flock_parameters_.d / norm(p.getPosition() - boid.getPosition()) * flock_parameters_.s * p.getVelocity());
      } // l'obiettivo è farlo funzionare come separation, al momento lo lascio così

      // Vector corrections_predator;
      // std::vector<Boid> preys;
      // const float d = flock_parameters_.d;

      // std::for_each(flock_.begin(), flock_.end(), [p, d, &preys](Boid const& b) {
      //   if (p.hasNeighbour(b, d)) {
      //     preys.push_back(b);
      //   };
      // });

      // if (std::find_if(preys.begin(), preys.end(), [boid](Boid const& prey) { return prey == boid; }) != preys.end()) {
      //   corrections_predator = (flock_parameters_.d / norm(p.getPosition() - boid.getPosition()) * flock_parameters_.s * p.getVelocity()); // il flock_parameters_.s è il vecchio par.s
      // }

      auto newVel = boid.getVelocity() + flock_parameters_.a * corrections.alignment + flock_parameters_.c * corrections.cohesion // /100.F (No factor)
                  - flock_parameters_.s * corrections.separation + corrections.separation_predator;

      Boid modified_boid(boid.getPosition() + newVel / (dt), newVel);

      overlapping(modified_boid); // io la ho messa membro di flock, si potrebbe anche mettere membro di Boid
                                  // però anziche passare un boid dovrei passare il flock

      modified_boid.biological_limits();
      modified_boid.correct_borders();
      modified_flock.push_back(modified_boid);
    } else {
      Boid modified_boid(boid.getPosition() + boid.getVelocity() / (dt), boid.getVelocity());
      modified_flock.push_back(modified_boid);
    }
  }

  flock_ = modified_flock;
}

void Flock::overlapping(Boid& modified_boid)
{
  std::for_each(flock_.begin(), flock_.end(), [&modified_boid](Boid const& other) {
    if (other == modified_boid) {
      modified_boid.setPosition(modified_boid.getPosition() + generateCoordinates(-1.f, 1.f));
    };
  });
}
} // namespace bd
