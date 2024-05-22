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

float norm(Vector const&);
} // namespace bd

#endif