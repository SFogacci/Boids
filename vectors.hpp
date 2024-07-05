#ifndef VECTORS_HPP
#define VECTORS_HPP

namespace bd {

struct Vector
{
  float x{};
  float y{};

  Vector operator+=(Vector const&);
};

constexpr bd::Vector windowDimensions{800.f, 600.f};

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