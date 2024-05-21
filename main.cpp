#include "boid.hpp"
#include "vectors.hpp"
#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"

auto bd::Boid::moveBoid(bd::Flock const& flock, bd::Boid& b, float const d,
                        float const ds, float s, float const a, float const c)
{
  auto v = (flock.separation(b, ds, s) + flock.alignment(b, d, a))
         + flock.cohesion(b, d, c);
  b.setVelocity(v + b.getVelocity());
  b.setPosition(b.getPosition() + ((1.f / 60.f) * b.getVelocity() ));
  b.getOrientation();
}

 void gameLoop(bd::Flock & flock, float const d, float const d_s,
                float const s, float const a, float const c)
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
      for (auto it = flock.flock().begin(), last = flock.flock().end(); it != last; ++it) {
        window.draw(it->birdShape);
        // std::cout << " " << it->getVelocity().x << std::endl; //debug
        it->moveBoid(flock, it, d, d_s, s, a, c);
      }

      window.display();
    }
  }


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

  bd::Flock flock(b1);
  bd::Flock flock(b2);
  bd::Flock flock(b3);
  bd::Flock flock(b4);

  std::cout << "Flock size is " << flock.flock().size() << '\n';

void gameLoop(bd::Flock & flock, float const d, float const d_s,
                float const s, float const a, float const c);
 
}
