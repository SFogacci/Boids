#include "boids.hpp"
#include <cmath>
#include <vector>


int main()
{
  bd::Boid b1{{0, 0}, {1, 1}};
  bd::Boid b2{{1, 0}, {-1, 1}};
  bd::Boid b3{{0, 1}, {1, -1}};
  bd::Boid b4{{1, -1}, {-1, -1}};

  std::vector<bd::Boid> flock{};
  flock.push_back(b1);
  flock.push_back(b2);
  flock.push_back(b3);
  flock.push_back(b4);
};
