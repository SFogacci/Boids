#include <iostream>

#include "boid.hpp"
namespace bd {




auto createBirds(const size_t& n)
{
  std::vector<Boid> birds;
  birds.reserve(n);

  for (size_t i = 0; i != n; ++i) {
    Boid bird{generateCoordinate(0.f, 900.f), generateCoordinate(-5.f, 5.f)};
    birds.push_back(bird);
  }
  return birds;
}

auto createPredators(){
  Predator bird{generateCoordinate(0.f, 900.f), generateCoordinate(-5.f, 5.f)};
  return bird;
}


} // namespace bd
