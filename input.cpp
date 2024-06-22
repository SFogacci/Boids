#include <iostream>

#include "boid.hpp"
namespace bd {




auto createBirds(const size_t& n)
{
  std::vector<Boid> birds;
  birds.reserve(n);

  for (size_t i = 0; i != n; ++i) {
    while (true) {
      Boid bird{generateCoordinate(0.f, 900.f), generateCoordinate(-5.f, 5.f)};
      if (norm(bird.getVelocity()) > 0.5) {
        birds.push_back(bird);
        break;
      }
    }
  }
  return birds;
}

auto createPredators(){
  Predator bird{generateCoordinate(0.f, 900.f), generateCoordinate(-5.f, 5.f)};
  return bird;
}


} // namespace bd
