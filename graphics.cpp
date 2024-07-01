#include "graphics.hpp"
#include "statistics.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace bd {
sf::ConvexShape birdShape;
sf::ConvexShape setShape(bd::Boid const& b) // passaggio by const ref
{
  birdShape.setPointCount(3);
  birdShape.setPoint(
      0, sf::Vector2f(b.getPosition().x - 5.f, b.getPosition().y - 2.f));
  birdShape.setPoint(1,
                     sf::Vector2f(b.getPosition().x + 4.f, b.getPosition().y));
  birdShape.setPoint(
      2, sf::Vector2f(b.getPosition().x - 5.f, b.getPosition().y + 2.f));
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

void gameLoop(Flock& flock, Predator& p)
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(w_window, h_window), "Boids",
                          sf::Style::Default, settings);
  window.setFramerateLimit(60);
  window.setPosition(sf::Vector2i(0, 0));

  std::ofstream outfile{"statistics.txt"};
  if (!outfile) {
    throw std::runtime_error{"Impossible to open file!"};
  }
  auto iteration{0};

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    Predator predator_container = flock.predator_evolution(p);
    flock.evolution(p);
    p = predator_container;

    window.clear();

    window.draw(setShape(p));
    std::for_each(flock.getFlock().begin(), flock.getFlock().end(),
                  [&window](Boid const& b) { window.draw(setShape(b)); });
    window.display();

    auto stats{statistics(flock)};
    outfile << iteration << ' ' << stats.speedStats.mean << ' '
            << stats.speedStats.sigma << ' ' << stats.distanceStats.mean << ' '
            << stats.distanceStats.sigma << '\n';
    std::cout << "Iteration: " << iteration << '\n' << printStatistics(stats);
    ++iteration;
  }
}

void drawGraph(TGraph& graph)
{
  graph.SetLineColor(kAzure + 4);
  // auto ctitle{title.c_str()};
  // graph.SetTitle(";iterations;");
  // graph.SetTitle(ctitle);
  graph.Draw("AC");
}
} // namespace bd