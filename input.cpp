#include "boid.hpp"
#include "vectors.hpp"
namespace bd {

auto createBird(bool isPredator)
{
  float x = generateCoordinate(0.f, static_cast<float>(windowDimensions.x));
  float y = generateCoordinate(0.f, static_cast<float>(windowDimensions.y));
  Vector position{x, y};
  while (true) {
    float v_x = generateCoordinate(-maximumSpeed, maximumSpeed);
    float v_y = generateCoordinate(-maximumSpeed, maximumSpeed);
    Vector velocity{v_x, v_y};
    if (norm(velocity) > minimumSpeed && norm(velocity) < maximumSpeed) {
      Boid bird{position, velocity, isPredator};
      return bird;
    }
  }
}

auto createPreys(int n)
{
  std::vector<Boid> birds;
  birds.reserve(static_cast<std::size_t>(n));

  for (int i = 0; i != n; ++i) {
    birds.push_back(createBird(0));
  }
  overlapping(birds);
  return birds;
}

} // namespace bd
