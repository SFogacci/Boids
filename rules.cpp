#include "vectors_functions.hpp"

namespace bd {
bool is_near(Boid const& a, Boid const& b, float d)
{
  d = 12.;
  return distance(a, b) <= d;
}

Vector separation(Boid const& b, std::vector<Boid> a, float s)
{
  float d{};
  Vector v_sep{};
  {
    auto et = a.begin();
    while (et != a.end())
      if (is_near(b, *et, d) == true) {
        v_sep = vecsum(
            vecmul(vecdif((b).getPosition(), (*et).getPosition()), -s), v_sep);
      }
    ++et;
  }
  return v_sep;
}

Vector alignment(Boid const& b, std::vector<Boid> c, float a)
{
  float d{};
  int i{};
  Vector v_ali{};
  auto et = c.begin();
  while (et != c.end()) {
    if (is_near(b, *et, d) == true) {
      v_ali = vecsum(vecdif((b).getVelocity(), (*et).getVelocity()), v_ali);
      ++i;
    }
    ++et;
  }
  return vecmul(v_ali, a / (static_cast<float>(i) - 1));
}

Vector center_of_mass(Boid a, std::vector<Boid> b)
{
  int i{};
  float d{};
  Vector x_center;
  auto it = b.begin();
  while (it != b.end()) {
    if (is_near(*it, a, d) == true) {
      x_center = vecsum((*it).getPosition(), x_center);
      ++i;
    }
    ++it;
  }
  return vecmul(x_center, 1 / (static_cast<float>(i) - 1));
}

Vector cohesion(Boid const& a, std::vector<Boid> b, float c)
{
  return vecmul(vecdif(a.getPosition(), center_of_mass(a, b)), c);
}

} // namespace bd