#ifndef VECTORS_HPP
#define VECTORS_HPP

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

Vector generateCoordinates(float a, float b);

void normalize(Vector&, float);
} // namespace bd

#endif