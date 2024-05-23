#include "boid.hpp"
#include "vectors.hpp"
#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>

void gameLoop(bd::Flock& flock)
{
  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids");
  window.setFramerateLimit(60);
  // window.setPosition(sf::Vector2i(1920, -200));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    flock.evolution();
    for (auto it = flock.flock().begin(), last = flock.flock().end();
         it != last; ++it) {
      window.draw(it->birdShape);
    }

    window.display();
  }
}

int main()
{
  bd::Parameters par{0.5f, 0.5f, 10.f, 1.f, 0.5f};

  bd::Boid b1{{100, 255}, {0.1, 0.1}};
  bd::Boid b2{{200, 306}, {0.3, 0.11}};
  bd::Boid b3{{259, 404}, {0.1, -0.5}};
  bd::Boid b4{{158, 90}, {-0.1, -0.1}};
  bd::Boid b5{{100, 98}, {0.1, 0.1}};
  bd::Boid b6{{705, 305}, {0.3, 0.45}};
  bd::Boid b7{{534, 76}, {0.1, -0.31}};
  bd::Boid b8{{696, 90}, {-0.11, -0.1}};

  std::vector storno{b1, b2, b3, b4, b5, b6, b7, b8};

  bd::Flock flock{storno, par};

  std::cout << "Flock size is " << static_cast<int>(flock.flock().size()) << '\n';

  gameLoop(flock);
}
