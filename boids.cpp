#include "vectors_functions.hpp"
#include <cmath>
#include <vector>
#include <iostream>

int main()
{
  float s{1.f};
  float a{1.f};
  float c{1.f};

  bd::Boid b1{{0, 0}, {1, 1}};
  bd::Boid b2{{1, 0}, {-1, 1}};
  bd::Boid b3{{0, 1}, {1, -1}};
  bd::Boid b4{{1, -1}, {-1, -1}};

  std::vector<bd::Boid> flock{};
  flock.push_back(b1);
  flock.push_back(b2);
  flock.push_back(b3);
  flock.push_back(b4);

  for (bd::Boid bo : flock) {
    bd::Vector v_f = vecsum(
        vecsum(vecsum(bo.getVelocity(), separation( bo, flock, s)), alignment(bo, flock, a)), cohesion(bo, flock, c));
        std::cout << static_cast<int>(v_f.x) << " " << static_cast<int>(v_f.y) << "/n";
  }
};
