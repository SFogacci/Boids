#ifndef VECTORS_HPP
#define VECTORS_HPP

namespace bd {
struct Vector
{
  double x{};
  double y{};

  Vector operator+=(Vector const&);
};

Vector operator+(Vector const&, Vector const&);

Vector operator*(double, Vector const&);

Vector operator-(Vector const&, Vector const&);

Vector operator/(Vector const&, double);

double norm(Vector const&);
} // namespace bd

#endif