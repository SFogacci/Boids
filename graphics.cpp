#include "graphics.hpp"
#include "statistics.hpp"
#include <fstream>

namespace bd {
sf::ConvexShape birdShape;
sf::ConvexShape predatorShape;
sf::ConvexShape setShape(bd::Boid const& b) // passaggio by const ref
{
  if (!b.isPredator()) {
    birdShape.setPointCount(3);
    birdShape.setPoint(0, sf::Vector2f(b.getPosition().x - 5.f, b.getPosition().y - 2.5f));
    birdShape.setPoint(1, sf::Vector2f(b.getPosition().x + 5.f, b.getPosition().y));
    birdShape.setPoint(2, sf::Vector2f(b.getPosition().x - 5.f, b.getPosition().y + 2.5f));
    birdShape.setFillColor(sf::Color::Green);
    birdShape.setOutlineColor(sf::Color::Black);
    birdShape.setOutlineThickness(1.f);
    birdShape.setPosition(b.getPosition().x, b.getPosition().y);
    birdShape.setOrigin(b.getPosition().x, b.getPosition().y);
    birdShape.setRotation(b.getOrientation());
    return birdShape;
  } else {
    predatorShape.setPointCount(4);
    predatorShape.setPoint(0, sf::Vector2f(b.getPosition().x - 7.5f, b.getPosition().y - 5.f));
    predatorShape.setPoint(1, sf::Vector2f(b.getPosition().x + 7.5f, b.getPosition().y));
    predatorShape.setPoint(2, sf::Vector2f(b.getPosition().x - 7.5f, b.getPosition().y + 5.f));
    predatorShape.setPoint(3, sf::Vector2f(b.getPosition().x - 2.5f, b.getPosition().y));
    predatorShape.setFillColor(sf::Color::Red);
    predatorShape.setOutlineColor(sf::Color::Black);
    predatorShape.setOutlineThickness(1.f);
    predatorShape.setPosition(b.getPosition().x, b.getPosition().y);
    predatorShape.setOrigin(b.getPosition().x, b.getPosition().y);
    predatorShape.setRotation(b.getOrientation());
    return predatorShape;
  }
}

void gameLoop(Flock& flock, Boid& p)
{
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(windowDimensions.x), static_cast<unsigned int>(windowDimensions.y)), "Boids", sf::Style::Default, settings);
  window.setFramerateLimit(60);
  window.setPosition(sf::Vector2i(0, 0));

  std::ofstream outfile{"statistics.txt"};
  if (!outfile) {
    throw std::runtime_error{"Impossible to open file!"};
  }
  auto iteration{0};

  bool active{true};
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (sf::Event::KeyPressed == event.type && (sf::Keyboard::Escape == event.key.code)) {
        active = !active;
      }
    }

    if (active) {
      Boid modified_predator = p.predator_evolution(flock);
      flock.evolution(p);
      p = modified_predator;

      window.clear(sf::Color(113, 188, 225, 255)); 

      window.draw(setShape(p));
      std::for_each(flock.getFlock().begin(), flock.getFlock().end(), [&window](Boid const& b) { window.draw(setShape(b)); });
      window.display();

      auto stats{statistics(flock)};
      outfile << iteration << ' ' << stats.speedStats.mean << ' ' << stats.speedStats.sigma << ' ' << stats.distanceStats.mean << ' ' << stats.distanceStats.sigma << '\n';
      // std::cout << "Iteration: " << iteration << '\n' << printStatistics(stats);
      ++iteration;
    }
  }
}

void drawGraph(TGraph& graph, std::string const& title)
{
  graph.SetLineColor(kAzure + 4);
  const auto titles{title + ';' + "iterations" + ';' + title};
  graph.SetTitle(titles.c_str());
  graph.Draw("AC");
}
} // namespace bd