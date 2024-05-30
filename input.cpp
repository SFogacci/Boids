#include <iostream>
#include <random>

#include "boid.hpp"
namespace bd {

auto getParameters()
{
  float a;
  float c;
  float d;
  float ds;
  float s;

  Parameters parameters{a, c, d, ds, s};
  std::cout << "Insert flock's parameters: \n";
  std::cout << "Cohesion intensity [0,1]: ";
  std::cin >> c;
  std::cout << "allignment intensity [0,1]: ";
  std::cin >> a;
  std::cout << "Separation intensity [0,1]: ";
  std::cin >> s;
  std::cout << "Interaction distance [0, 100]: ";
  std::cin >> d;
  std::cout << "Separation distance [0, 20]: ";
  std::cin >> ds;
  return parameters;
}

auto getSize()
{
  size_t n;
  std::cout << "Number of boids: ";
  std::cin >> n;
  return n;
}

auto generateCoordinate(float a, float b) // limiti per la generazione delle velocità e posizioni. Le velocità possono essere anche negative, le coordinate no.                               
{
  std::random_device rd;
  std::uniform_real_distribution<> dis(a, b);
  Vector coordinates{static_cast<float>(dis(rd)), static_cast<float>(dis(rd))};
  return coordinates;
}

auto createBirds(size_t n)
{
  std::vector<Boid> birds;
  birds.reserve(n);

  for (size_t i = 0; i != n; ++i) {
    Boid bird{generateCoordinate(0.f, 900.f), generateCoordinate(-20.f, 20.f)};
    birds.push_back(bird);
  }
  return birds;
}

} // namespace bd