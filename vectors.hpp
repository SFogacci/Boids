#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <cmath>

namespace bd {

struct Vector
{
  float x{};
  float y{};

  Vector operator+=(Vector const&);
};

Vector operator+(Vector const&, Vector const&);

Vector operator*(float, Vector const&);

Vector operator-(Vector const&, Vector const&);

Vector operator/(Vector const&, float);

bool operator==(Vector const&, Vector const&);

float norm(Vector const&);

float generateCoordinate(float, float);

void normalize(Vector&, float);

Vector toroidalDifference(Vector const&, Vector const&);

const float pi{std::atan(1.f) * 4};
constexpr float maximumSpeed{5.f};
constexpr float minimumSpeed{0.5f};
constexpr Vector windowDimensions{800.f, 600.f};
} // namespace bd

#endif