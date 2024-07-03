#include "boid.hpp"
#include "vectors.hpp"
#include <iostream>
namespace bd {

auto createBirds(const std::size_t& n)
{
  std::vector<Boid> birds;
  birds.reserve(n);

  for (std::size_t i = 0; i != n; ++i) {
    Boid bird{
        Vector{
            generateCoordinates(0.f, static_cast<float>(windowDimensions.x)),
            generateCoordinates(0.f, static_cast<float>(windowDimensions.y))},
        {}};
    while (true) {
      auto velocity{Vector{
          generateCoordinates(-5.f, 5.f),
          generateCoordinates(-5.f, 5.f)}}; // da cambiare in variabili (const)
      if (norm(velocity) > 5.f) {
        bird.setVelocity(velocity);
        birds.push_back(bird);
        break;
      }
    }
  }

  return birds;
}

auto createPredator()
{
  Boid bird{
      Vector{generateCoordinates(0.f, static_cast<float>(windowDimensions.x)),
             generateCoordinates(0.f, static_cast<float>(windowDimensions.y))},
      {},
      1};
  while (true) {
    auto velocity{Vector{
        generateCoordinates(-5.f, 5.f),
        generateCoordinates(-5.f, 5.f)}}; // da cambiare in variabili (const)
    if (norm(velocity) > 5.f) {
      bird.setVelocity(velocity);
      break;
    }
  }
  return bird;
}

} // namespace bd
