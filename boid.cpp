#include "boid.hpp"
#include "vectors.hpp"
#include <cassert>
#include <numeric>

namespace bd {

bool operator==(Boid const& a, Boid const& b)
{
  return (a.getVelocity() == b.getVelocity()
          && a.getPosition() == b.getPosition());
}

void Boid::correctBorders()
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
  if (norm(velocity_) > maximumSpeed) {
    normalize(velocity_, maximumSpeed);
  }
}

Boid Boid::predatorEvolution(Flock const& f) const
{
  assert(isPredator_);
  auto copy{*this};
  const auto flock{f.getFlock()};
  const auto parameters{f.getFlockParameters()};
  const float d{2.f * parameters.d};

  const auto preys = static_cast<float>(
      std::count_if(flock.begin(), flock.end(),
                    [&](auto const& boid) { return hasNeighbour(boid, d); }));
  assert(preys >= 0.f);

  if (preys != 0.f) {
    const auto center_of_mass = std::accumulate(
        flock.begin(), flock.end(), Vector{}, [&](auto& sum, auto const& boid) {
          if (hasNeighbour(boid, d)) {
            auto difference = toroidalDifference(boid.getPosition(), position_);
            sum += getPosition() + difference;
          }
          return sum;
        });

    const auto hunting = toroidalDifference(center_of_mass / preys, position_);
    copy.setVelocity(velocity_ + hunting);
    copy.biologicalLimits();
  }

  copy.setPosition(position_ + copy.getVelocity());
  copy.correctBorders();

  return copy;
}

void overlapping(std::vector<Boid>& birds)
{
  for (Boid& boid : birds) {
    std::for_each(birds.begin(), birds.end(), [&](Boid const& other) {
      if (other.getPosition() == boid.getPosition()) {
        boid.setPosition(
            boid.getPosition()
            + Vector{generateCoordinate(-minimumSpeed, minimumSpeed),
                     generateCoordinate(-minimumSpeed, minimumSpeed)});
      }
    });
  }
}

void Flock::evolution(Boid const& p)
{
  assert(p.isPredator());
  std::vector<Boid> modifiedFlock{};
  modifiedFlock.reserve(flock_.size());

  for (Boid const& boid : flock_) {

    Boid modifiedBoid(boid);
    if (boid.hasNeighbour(p, flockParameters_.d)) {
      const auto separation_predator =
          toroidalDifference(boid.getPosition(), p.getPosition());
      modifiedBoid.setVelocity(boid.getVelocity()
                               + flockParameters_.s * separation_predator);
    }

    const auto neighbours = static_cast<float>(
        std::count_if(flock_.begin(), flock_.end(), [&](auto const& other) {
          return boid.hasNeighbour(other, flockParameters_.d);
        }));
    assert(neighbours >= 0.f);

    if (neighbours != 0.f) {
      auto corrections = std::accumulate(
          flock_.begin(), flock_.end(), Corrections{},
          [&](auto& sums, auto const& other) {
            if (boid.hasNeighbour(other, flockParameters_.d)) {

              auto distance =
                  toroidalDifference(other.getPosition(), boid.getPosition());
              sums.alignment += other.getVelocity();
              sums.cohesion += distance;

              if (boid.hasNeighbour(other, flockParameters_.ds)) {
                normalize(distance, flockParameters_.ds / norm(distance));
                sums.separation += distance;
              }
            }
            return sums;
          });

      corrections.alignment =
          corrections.alignment / neighbours - boid.getVelocity();
      corrections.cohesion = corrections.cohesion / neighbours;

      modifiedBoid.setVelocity(modifiedBoid.getVelocity()
                               + flockParameters_.a * corrections.alignment
                               + flockParameters_.c * corrections.cohesion
                               - flockParameters_.s * corrections.separation);
    }
    modifiedBoid.biologicalLimits();

    modifiedBoid.setPosition(modifiedBoid.getPosition()
                             + modifiedBoid.getVelocity());
    modifiedBoid.correctBorders();
    overlapping(modifiedFlock);
    modifiedFlock.push_back(modifiedBoid);
  }

  flock_ = modifiedFlock;
}

} // namespace bd
