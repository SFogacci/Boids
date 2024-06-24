#include "boid.hpp"
#include "vectors.hpp"
#include <iostream>
namespace bd {

auto createBirds(const std::size_t& n)
{
  std::vector<Boid> birds;
  birds.reserve(n);

  for (std::size_t i = 0; i != n; ++i) {
    Boid bird{generateCoordinates(0.f, 900.f), {}};
    while (true) {
      auto velocity{generateCoordinates(-5.f, 5.f)};
      if (norm(velocity) > 0.5) {
        bird.setVelocity(velocity);
        birds.push_back(bird);
        break;
      }
    }
  }
  return birds;
}

auto createPredators()
{
  Predator bird{generateCoordinates(0.f, 900.f),
                generateCoordinates(-5.f, 5.f)};
  return bird;
}

} // namespace bd
