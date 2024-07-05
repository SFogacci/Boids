#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "TGraph.h"
#include "boid.hpp"
#include <string>
#include "SFML/Graphics.hpp"

namespace bd {

sf::ConvexShape setShape(Boid const&);

void gameLoop(Flock&, Boid&);

void drawGraph(TGraph&, std::string const&);

} // namespace bd

#endif
