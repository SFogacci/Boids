#include "graphics.hpp"

namespace bd {
  sf::ConvexShape birdShape;
sf::ConvexShape setShape(bd::Boid const& b) // passaggio by const ref
{
  birdShape.setPointCount(3);
  birdShape.setPoint(
      0, sf::Vector2f(b.getPosition().x - 10.f, b.getPosition().y - 5.f));
  birdShape.setPoint(1,
                     sf::Vector2f(b.getPosition().x + 10.f, b.getPosition().y));
  birdShape.setPoint(
      2, sf::Vector2f(b.getPosition().x - 10.f, b.getPosition().y + 5.f));
  birdShape.setFillColor(sf::Color::Red);
  birdShape.setOutlineColor(sf::Color::White);
  birdShape.setOutlineThickness(1.f);
  birdShape.setPosition(b.getPosition().x, b.getPosition().y);
  birdShape.setOrigin(b.getPosition().x, b.getPosition().y);
  birdShape.setRotation(b.getOrientation());
  return birdShape;
}

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
      window.draw(setShape(*it));
    }

    window.display();
  }
}
} // namespace bd