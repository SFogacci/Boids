#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boid.hpp"
#include "doctest.h"
#include "vectors.hpp"

namespace bd {
TEST_CASE("One boid, all rules")
{
  Boid b1{{1.f, 1.f}, {1.f, 1.f}};
  std::vector birds{b1};
  Parameters parameters{0.5f, 0.5f, 2.f, 1.5f, 0.5f};
  Flock flock{birds, parameters};
  flock.evolution();
  CHECK(b1.getPosition().x == doctest::Approx(1));
  CHECK(b1.getPosition().y == doctest::Approx(1));

  CHECK(b1.getVelocity().x == doctest::Approx(1));
  CHECK(b1.getVelocity().y == doctest::Approx(1));
}

TEST_CASE("Two boids, separation only")
{
  Boid b1{{1.f, 1.f}, {0.f, 0.f}};
  Boid b2{{2.f, 1.f}, {0.f, 0.f}};
  std::vector birds{b1, b2};
  Parameters parameters{0.f, 0.f, 2.f, 1.5f, 0.5f};
  Flock flock{birds, parameters};
  flock.evolution();
  CHECK(b1.getPosition().x == doctest::Approx(0.5));
  CHECK(b1.getPosition().y == doctest::Approx(1));
  CHECK(b2.getPosition().x == doctest::Approx(2.5));
  CHECK(b2.getPosition().y == doctest::Approx(1));

  CHECK(b1.getVelocity().x == doctest::Approx(-0.5));
  CHECK(b1.getVelocity().y == doctest::Approx(0));
  CHECK(b2.getVelocity().x == doctest::Approx(0.5));
  CHECK(b2.getVelocity().y == doctest::Approx(0));
}

TEST_CASE("Two boids, cohesion only")
{
  Boid b1{{1.f, 1.f}, {0.f, 0.f}};
  Boid b2{{2.f, 1.f}, {0.f, 0.f}};
  std::vector birds{b1, b2};
  Parameters parameters{0.f, 0.5f, 2.f, 1.5f, 0.f};
  Flock flock{birds, parameters};
  flock.evolution();
  CHECK(b1.getPosition().x == doctest::Approx(1.5));
  CHECK(b1.getPosition().y == doctest::Approx(1));
  CHECK(b2.getPosition().x == doctest::Approx(1.5));
  CHECK(b2.getPosition().y == doctest::Approx(1));

  CHECK(b1.getVelocity().x == doctest::Approx(0.5));
  CHECK(b1.getVelocity().y == doctest::Approx(0));
  CHECK(b2.getVelocity().x == doctest::Approx(-0.5));
  CHECK(b2.getVelocity().y == doctest::Approx(0));
}

TEST_CASE("Two boids, alignment only: one still.")
{
  Boid b1{{1.f, 1.f}, {0.f, 1.f}};
  Boid b2{{2.f, 1.f}, {0.f, 0.f}};
  std::vector birds{b1, b2};
  Parameters parameters{0.5f, 0.f, 2.f, 1.5f, 0.f};
  Flock flock{birds, parameters};
  flock.evolution();
  CHECK(b1.getPosition().x == doctest::Approx(1));
  CHECK(b1.getPosition().y == doctest::Approx(1.5));
  CHECK(b2.getPosition().x == doctest::Approx(2));
  CHECK(b2.getPosition().y == doctest::Approx(1.5));

  CHECK(b1.getVelocity().x == doctest::Approx(0));
  CHECK(b1.getVelocity().y == doctest::Approx(0.5));
  CHECK(b2.getVelocity().x == doctest::Approx(0));
  CHECK(b2.getVelocity().y == doctest::Approx(0.5));
}

TEST_CASE("Overlap of two boids")
{
  Boid b1{{1.f, 1.f}, {0.f, 1.f}};
  Boid b2{{1.f, 1.f}, {0.f, -1.f}};
  std::vector birds{b1, b2};
  Parameters parameters{0.5f, 0.5f, 2.f, 1.5f, 0.5f};
  Flock flock{birds, parameters};
  flock.evolution();
  CHECK(b1.getPosition().x == doctest::Approx(1));
  CHECK(b1.getPosition().y == doctest::Approx(1));
  CHECK(b2.getPosition().x == doctest::Approx(1));
  CHECK(b2.getPosition().y == doctest::Approx(1));

  CHECK(b1.getVelocity().x == doctest::Approx(0));
  CHECK(b1.getVelocity().y == doctest::Approx(0));
  CHECK(b2.getVelocity().x == doctest::Approx(0));
  CHECK(b2.getVelocity().y == doctest::Approx(0));
}
} // namespace bd