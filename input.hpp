#ifndef INPUT_HPP
#define INPUT_HPP

#include "boid.hpp"
namespace bd {

Parameters getParameters();

size_t getSize();

Vector generateCoordinate(float a, float b);

std::vector<Boid> createBirds(size_t);

} // namespace bd
#endif