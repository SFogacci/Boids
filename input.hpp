#ifndef INPUT_HPP
#define INPUT_HPP

#include "boid.hpp"
namespace bd {

Vector generateCoordinate(float a, float b);
Predator createPredators();
std::vector<Boid> createBirds(const size_t&);

} // namespace bd
#endif
