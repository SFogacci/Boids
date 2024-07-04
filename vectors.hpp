#ifndef VECTORS_HPP
#define VECTORS_HPP

#include "SFML/Graphics.hpp"

namespace bd {

struct Vector
{
  float x{};
  float y{};

  Vector operator+=(Vector const&);
};

// inline const bd::Vector windowDimensions{
//     0.75f * static_cast<float>(sf::VideoMode::getDesktopMode().width),
//     0.75f * static_cast<float>(sf::VideoMode::getDesktopMode().height)};

inline const bd::Vector windowDimensions{800.f, 600.f};

Vector operator+(Vector const&, Vector const&);

Vector operator*(float, Vector const&);

Vector operator-(Vector const&, Vector const&);

Vector operator/(Vector const&, float);

bool operator==(Vector const&, Vector const&);

float norm(Vector const&);

float generateCoordinate(float a, float b);

void normalize(Vector&, float);

Vector toroidalDifference(Vector const&, Vector const&);
} // namespace bd

#endif