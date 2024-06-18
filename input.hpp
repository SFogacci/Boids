#ifndef INPUT_HPP
#define INPUT_HPP

#include "boid.hpp"
namespace bd {

Parameters getParameters();

std::size_t getSize();

Vector generateCoordinate(float a, float b);

std::vector<Boid> createBirds(std::size_t);

} // namespace bd
#endif