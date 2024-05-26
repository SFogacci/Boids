#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "boid.hpp"
#include "vectors.hpp"
#include "SFML/Graphics.hpp"

namespace bd {
sf::ConvexShape setShape(Boid const&);
void gameLoop(bd::Flock& flock);
} // namespace bd

#endif 