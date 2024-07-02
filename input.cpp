#include "boid.hpp"
#include "vectors.hpp"
#include <iostream>
namespace bd {

auto createBird(bool is_predator)
{
  float x = generateCoordinate(0.f, static_cast<float>(windowDimensions.width));
  float y = generateCoordinate(0.f, static_cast<float>(windowDimensions.height));
  Vector position{x, y};
  Boid bird{position, {}, is_predator};
  while (true) {
    float v_x = generateCoordinate(-5.f, 5.f);
    float v_y = generateCoordinate(-5.f, 5.f);
    Vector velocity{v_x, v_y};
    if (norm(velocity) > 0.5) {
      bird.setVelocity(velocity);
      return bird;
    }
  }
}

auto createPreys(const std::size_t n)
{
  std::vector<Boid> birds;
  birds.reserve(n);

  for (std::size_t i = 0; i != n; ++i) {
    birds.push_back(createBird(0));
  }
  return birds;
}


} // namespace bd
