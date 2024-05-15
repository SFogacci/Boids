#include "boid.hpp"
#include "vectors.hpp"
#include <iostream>

// int main()
// {
// bd::Boid b;
// bd::Vector v {1, 0};
// b.setVelocity(v);
// auto [x, y] = b.getVelocity();
// std::cout << x << ' ' << y << '\n';
// }

int main()
{
  auto d{1.2};
  auto ds{1.}; // ds < d
  auto s{1.};
  auto a{0.5}; // a < 1
  auto c{1.};

  bd::Boid b1{{0, 0}, {1, 1}};
  bd::Boid b2{{1, 0}, {-1, 1}};
  bd::Boid b3{{0, 1}, {1, -1}};
  bd::Boid b4{{1, 1}, {-1, -1}};

  bd::Boid::Flock flock{b1, b2, b3, b4};
  std::cout << "Flock size is " << flock.size() << '\n';

  for (auto& b : flock) {
    bd::Vector newVel = b.getVelocity() + b.separation(flock, ds, s)
                      + b.alignment(flock, d, a) + b.cohesion(flock, d, c);
    std::cout << newVel.x << " " << newVel.y << "\n";
    b.setVelocity(newVel);
    b.setPosition(b.getPosition() + newVel); // i boids successivi lavoreranno
                                             // con le nuove velocità di quelli precedenti, va bene?
  }
}