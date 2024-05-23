#include "boid.hpp"
#include "vectors.hpp"
#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>

void gameLoop(bd::Flock& flock)
{
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Boids");
  window.setFramerateLimit(60);
  window.setPosition(sf::Vector2i(1920, -200));

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
  bd::Parameters par{0.5f, 1.f, 1.2f, 1.f, 1.f};

  bd::Boid b1{{0, 0}, {1, 1}};
  bd::Boid b2{{1, 0}, {-1, 1}};
  bd::Boid b3{{0, 1}, {1, -1}};
  bd::Boid b4{{1, 1}, {-1, -1}};

  std::vector storno{b1, b2, b3, b4};

  bd::Flock flock{storno, par};

  std::cout << "Flock size is " << flock.flock().size() << '\n';

  void gameLoop(bd::Flock & flock);
}
