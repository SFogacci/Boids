#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "boid.hpp"
#include "SFML/Graphics.hpp"

namespace bd {
sf::ConvexShape setShape(Boid const&);
sf::ConvexShape setShape(Predator const&);
void gameLoop(bd::Flock& flock, Predator &p);
} // namespace bd

#endif 
