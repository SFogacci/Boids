#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "TGraph.h"
#include "boid.hpp"
#include "SFML/Graphics.hpp"
#include <string>

namespace bd {

sf::ConvexShape setShape(Boid const&);

void gameLoop(Flock&, Predator&);

void drawGraph(TGraph&);

} // namespace bd

#endif
