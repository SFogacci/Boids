#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "boid.hpp"

namespace bd {
sf::ConvexShape setShape(Boid const&);
void gameLoop(bd::Flock&);
} // namespace bd

#endif 
