#include "vectors.hpp"
#include <cassert>
#include <cmath>
#include <random>

namespace bd {

Vector Vector::operator+=(Vector const& add)
{
  return {x += add.x, y += add.y};
}

Vector operator+(Vector const& a, Vector const& b)
{
  auto sum = a;
  return sum += b;
}

Vector operator*(float c, Vector const& v)
{
  return {c * v.x, c * v.y};
}

Vector operator-(Vector const& a, Vector const& b)
{
  return a + (-1.f) * b;
}

Vector operator/(Vector const& v, float d)
{
  assert(d != 0); // da ottimizzare con exception ad esempio
  return 1.f / d * v;
}

bool operator==(Vector const& v, Vector const& p)
{
  return (v.x == p.x && v.y == p.y);
}

float norm(Vector const& v)
{
  return std::hypot(v.x, v.y);
}

float generateCoordinate(float a, float b)
{
  std::random_device rd;
  std::uniform_real_distribution<float> dis(a, b);
  float coordinate{dis(rd)};
  return coordinate;
}

void normalize(Vector& v, float f)
{
  v = f / norm(v) * v;
}
float toroidalDistance(
    float pos1, float pos2,
    float maxVal) // nello spazio toridale, lungo ciascun asse, la massima
{                 // distanza tra due boids diventa pari a metà della
  float dist =
      std::abs(pos1 - pos2); // dimensione della finestra lungo quell'asse.
  if (dist > maxVal / 2) { // Dati due boids, tra di loro ci sono due distanze:
                           // quella toroidale,
    dist = maxVal - dist; // che trapassa i bordi, e quella normale. La funzione
                          // restituisce la
  } // minima tra le due.
  return dist;
}

Vector toroidalDifference(Vector const& pos1, Vector const& pos2,
                          SpaceDimensions dim) // Crea un vettore che contiene
                                               // le distanze lungo i due assi
{ // tra due boids: i segni sono attribuiti in modo da
  float xDiff =
      pos1.x - pos2.x; // far funzionare correttamente separation e cohesion.
  float yDiff = pos1.y - pos2.y;

  if (std::abs(xDiff) > dim.width / 2) {
    xDiff = dim.width - std::abs(xDiff);
    xDiff *= (pos1.x > pos2.x) ? -1 : 1;
  }

  if (std::abs(yDiff) > dim.height / 2) {
    yDiff = dim.height - std::abs(yDiff);
    yDiff *= (pos1.y > pos2.y) ? -1 : 1;
  }

  return Vector{xDiff, yDiff};
}

} // namespace bd