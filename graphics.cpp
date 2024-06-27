#include "graphics.hpp"
#include "statistics.hpp"
#include <algorithm>
#include <iostream>

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

void gameLoop(bd::Flock& flock)
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids", sf::Style::Default,
                          settings);
  window.setFramerateLimit(60);
  window.setPosition(sf::Vector2i(0, 0));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    flock.evolution();

    window.clear();

    std::for_each(flock.getFlock().begin(), flock.getFlock().end(),
                  [&window](Boid const& b) { window.draw(setShape(b)); });
    window.display();
    std::cout << printStatistics(statistics(flock));
  }
}
} // namespace bd