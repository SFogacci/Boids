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

float generateCoordinate(float a, float b);

void normalize(Vector&, float);

float toroidalDistance(float, float, float);

struct SpaceDimensions
{
  float width;
  float height;
};

Vector toroidalDifference(Vector const&, Vector const&, SpaceDimensions);
} // namespace bd


#endif