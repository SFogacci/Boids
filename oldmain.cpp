#include "boid.hpp"
#include "vectors.hpp"
#include "graphics.hpp"
#include <cmath>
#include <iostream>

int main()
{
  bd::Parameters par{0.4f, 0.1f, 100.f, 10.f, 5.f};

  bd::Boid b1{{450, 210}, {50.f, -43.f}};
  bd::Boid b2{{430, 400}, {45.f, 21.f}};
  bd::Boid b3{{440, 105}, {-50.f, 35.f}};
  bd::Boid b4{{350, 610}, {50.f, -43.f}};
  bd::Boid b5{{530, 300}, {45.f, 21.f}};
  bd::Boid b6{{640, 805}, {90.f, 200.f}};
  bd::Boid b7{{350, 210}, {-50.f, -43.f}};
  bd::Boid b8{{230, 100}, {45.f, 111.f}};
  bd::Boid b9{{140, 205}, {50.f, 35.f}};
 
  std::vector storno{b1, b2, b3, b4, b5, b6, b7, b8, b9};

  bd::Flock flock{storno, par};

  gameLoop(flock);
}

