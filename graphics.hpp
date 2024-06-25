#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "boid.hpp"

namespace bd {
sf::ConvexShape setShape(Boid const&);
sf::ConvexShape setShape(Predator const&);
void gameLoop(bd::Flock&, Predator &);
} // namespace bd

#endif 
