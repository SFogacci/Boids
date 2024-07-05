#include "boid.hpp"
#include "vectors.hpp"
namespace bd {

auto createBird(bool isPredator)
{
  float x = generateCoordinate(0.f, static_cast<float>(windowDimensions.x));
  float y = generateCoordinate(0.f, static_cast<float>(windowDimensions.y));
  Vector position{x, y};
  Boid bird{position, {}, isPredator};
  while (true) {
    float v_x = generateCoordinate(-5.f, 5.f);
    float v_y = generateCoordinate(-5.f, 5.f);
    Vector velocity{v_x, v_y};
    if (norm(velocity) > 0.5) { // && norm(velocity) < 5.f, così possiamo togliere il controllo per la velocità del predator e metterlo nel for loop
      bird.setVelocity(velocity);
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
  return birds;
}


} // namespace bd
