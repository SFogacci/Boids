#include "graphics.hpp"
#include <iostream>

namespace bd {
sf::ConvexShape birdShape;                  // cercare di spostarlo nell'hpp
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
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(900, 900), "Boids", sf::Style::Default,
                          settings);
  sf::RenderWindow graphs(sf::VideoMode(900, 900), "Graphs");

  window.setFramerateLimit(60);
  graphs.setFramerateLimit(60);

  window.setPosition({0, 0});
  graphs.setPosition(
      {900, 0}); // parametri che poi dovremo trasformare in costanti

  while (window.isOpen()) {
    while (graphs.isOpen()) {
      sf::Event event;

      while (window.pollEvent(event) || graphs.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
          graphs.close();
          // } else if (event.type == sf::Event::Resized) {
          // fai in modo che non si possa fare il resize
          //   }
        }
      }

      window.clear();
      graphs.clear();

      flock.evolution();

      // positionGraph(flock, graphs);

      for (auto const& it : flock.getFlock()) {
        window.draw(setShape(it));
      }

      // std::vector<int> binned_vel = binning_velocities(flock);
      std::vector<sf::RectangleShape> vel_graph = graphing(
          binning_velocities(flock), graphs.getView().getSize().y / 3.f);
      for (auto const& it : vel_graph) {
        graphs.draw(it);
      }

      std::vector<sf::RectangleShape> dis_graph =
          graphing(binning_distances(flock), graphs.getView().getSize().y);
      for (auto const& it : dis_graph) {
        graphs.draw(it);
      }

      window.display();
      graphs.display();
    }
  }
}

std::vector<int>
binning_velocities(Flock const& flock) // prendo solo le norme delle velocità,
                                       // quindi sempre positive
{
  std::vector<int> binned_velocities(100, 0);

  for (auto const& it : flock.getFlock()) {
    if (norm(it.getVelocity()) <= 1000.f) {
      binned_velocities[static_cast<unsigned>((norm(it.getVelocity()) / 10))] +=
          1;
    } else {
      binned_velocities[99] += 1;
    }
  }

  return binned_velocities;
}

std::vector<int> binning_distances(Flock const& flock)
{
  std::vector<int> binned_distances(100, 0);
  float distance;
  for (auto const& boid : flock.getFlock()) {
    for (auto const& other : flock.getFlock()) {
      if (&other != &boid) {
        distance = norm(boid.getPosition() - other.getPosition());
        if (distance <= 1275.f)
          binned_distances[static_cast<unsigned>(distance / 12.75f)] += 1;
        else {
          binned_distances[99] += 1;
        }
      }
    }
  }
  return binned_distances;
}

std::vector<sf::RectangleShape>
graphing(std::vector<int> const& binned_stat,
         float const& side) // side sarebbe l'altezza, ma dato che è 900*900, lo
                            // chiamo side
{
  std::vector<sf::RectangleShape> graph;

  for (size_t i{0u}; i < binned_stat.size(); ++i) {
    sf::RectangleShape bar(
        sf::Vector2f(9.f, static_cast<float>(-binned_stat[i]) * 10.f));
    // std::cout << "binned_stat[" << i << "] = " << binned_stat[i] << '\n';
    bar.setPosition(static_cast<float>(i) * 9.f, side);
    bar.setFillColor(sf::Color::White);
    bar.setOutlineColor(sf::Color::Black);
    bar.setOutlineThickness(1.f);
    graph.push_back(bar);
  }

  return graph;
}
} // namespace bd