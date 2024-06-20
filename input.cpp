#include <iostream>
#include <random>

#include "boid.hpp"
namespace bd {



auto generateCoordinate(float a, float b)                            
{
  std::random_device rd;
  std::uniform_real_distribution<float> dis(a, b);
  Vector coordinates{dis(rd), dis(rd)};
  return coordinates;
}

auto createBirds(const size_t& n)
{
  std::vector<Boid> birds;
  birds.reserve(n);

  for (size_t i = 0; i != n; ++i) {
    Boid bird{generateCoordinate(0.f, 900.f), generateCoordinate(-0.05f, 0.05f)};
    birds.push_back(bird);
  }
  return birds;
}

} // namespace bd
