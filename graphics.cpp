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

sf::ConvexShape predatorShape;
sf::ConvexShape setShape(bd::Predator const& b)
{
  predatorShape.setPointCount(4);
  predatorShape.setPoint(
      0, sf::Vector2f(b.getPosition().x - 15.f, b.getPosition().y - 10.f));
  predatorShape.setPoint(
      1, sf::Vector2f(b.getPosition().x + 15.f, b.getPosition().y));
  predatorShape.setPoint(
      2, sf::Vector2f(b.getPosition().x - 15.f, b.getPosition().y + 10.f));
  predatorShape.setPoint(
      3, sf::Vector2f(b.getPosition().x - 5.f, b.getPosition().y));
  predatorShape.setFillColor(sf::Color::Green);
  predatorShape.setOutlineColor(sf::Color::White);
  predatorShape.setOutlineThickness(1.f);
  predatorShape.setPosition(b.getPosition().x, b.getPosition().y);
  predatorShape.setOrigin(b.getPosition().x, b.getPosition().y);
  predatorShape.setRotation(b.getOrientation());
  return predatorShape;
}

void gameLoop(bd::Flock& flock, Predator& p)
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
    flock.predator_evolution(p);
    // flock.evolution();
    window.draw(setShape(p));
    for (auto it = flock.getFlock().begin(), last = flock.getFlock().end();
         it != last; ++it) {
      window.draw(setShape(*it));
    }

    window.display();
  }
}
} // namespace bd