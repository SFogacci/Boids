#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "boid.hpp"
#include "SFML/Graphics.hpp"

namespace bd {

sf::ConvexShape setShape(Boid const&);

void gameLoop(bd::Flock& flock);

void positionGraph(Flock const&, sf::RenderWindow&);

std::vector<int> binning_velocities(Flock const&);

std::vector<int> binning_distances(Flock const&);

std::vector<sf::RectangleShape> graphing(std::vector<int> const&, float const&);

} // namespace bd

#endif
