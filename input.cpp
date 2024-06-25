#include "boid.hpp"
#include "vectors.hpp"
#include <iostream>
namespace bd {

auto createBirds(const std::size_t& n)
{
  std::vector<Boid> birds;
  birds.reserve(n);

  for (std::size_t i = 0; i != n; ++i) {
    Boid bird{generateCoordinates(0.f, static_cast<float>(h_window)), {}}; // sarebbe da modificare in modo che la posizione in x sia al masismo w_window e in y h_window
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
  Predator bird{generateCoordinates(0.f, static_cast<float>(h_window)),
                generateCoordinates(-5.f, 5.f)};
  return bird;
}

} // namespace bd
