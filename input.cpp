// #include "boid.hpp"
// #include "vectors.hpp"
// #include <iostream>
// namespace bd {

// auto createBirds(const int n)
// {
//   std::vector<Boid> birds;
//   birds.reserve(n);

//   for (int i = 0; i != n; ++i) {
//     const Vector position{generateCoordinates(0.f, static_cast<float>(windowDimensions.x)), generateCoordinates(0.f, static_cast<float>(windowDimensions.y))};
//     while (true) {
//       const Vector velocity{generateCoordinates(-5.f, 5.f), generateCoordinates(-5.f, 5.f)}; // da cambiare in variabili (const)
//       if (norm(velocity) > 5.f) {
//         Boid bird{position, velocity};
//         // std::for_each(birds.begin(), birds.end() - 2, [&bird](bd::Boid const& other) {
//         //   if (other.getPosition() == bird.getPosition()) {
//         //     bird.setPosition(bird.getPosition() + Vector{generateCoordinates(-1.f, 1.f), generateCoordinates(-1.f, 1.f)});
//         //   }
//         // });
//         overlapping(birds, bird);
//         birds.push_back(bird);
//         break;
//       }
//     }
//   }

//   return birds;
// }

// auto createPredator()
// {
//   Boid bird{Vector{generateCoordinates(0.f, static_cast<float>(windowDimensions.x)), generateCoordinates(0.f, static_cast<float>(windowDimensions.y))}, {}, 1};
//   while (true) {
//     auto velocity{Vector{generateCoordinates(-5.f, 5.f), generateCoordinates(-5.f, 5.f)}}; // da cambiare in variabili (const)
//     if (norm(velocity) > 5.f) {
//       bird.setVelocity(velocity);
//       break;
//     }
//   }
//   return bird;
// }

// } // namespace bd

#include "boid.hpp"
#include "vectors.hpp"
#include <iostream>
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
    if (norm(velocity) > 0.5) {
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
