#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boid.hpp"
#include "doctest.h"
#include "vectors.hpp"

namespace bd {
TEST_CASE("One boid, all rules")
{
  Boid b1{{101.f, 101.f}, {1.f, 1.f}};
  std::vector birds{b1};
  Parameters parameters{0.5f, 0.5f, 2.f, 1.5f, 0.5f};
  Flock flock{birds, parameters};
  flock.evolution();
  auto it = flock.flock().begin();
  CHECK(it->getPosition().x == doctest::Approx(102));
  CHECK(it->getPosition().y == doctest::Approx(102));
  
  CHECK(it->getVelocity().x == doctest::Approx(1));
  CHECK(it->getVelocity().y == doctest::Approx(1));
}

TEST_CASE("Two boids, separation only")
{
  Boid b1{{101.f, 101.f}, {0.f, 0.f}};
  Boid b2{{102.f, 101.f}, {0.f, 0.f}};
  std::vector birds{b1, b2};
  Parameters parameters{0.f, 0.f, 2.f, 1.5f, 0.5f};
  Flock flock{birds, parameters};
  flock.evolution();
  auto it = flock.flock().begin();
  auto et = it+1;
  CHECK(it->getPosition().x == doctest::Approx(100.5));
  CHECK(it->getPosition().y == doctest::Approx(101));
  CHECK(et->getPosition().x == doctest::Approx(102.5));
  CHECK(et->getPosition().y == doctest::Approx(101));

  CHECK(it->getVelocity().x == doctest::Approx(-0.5));
  CHECK(it->getVelocity().y == doctest::Approx(0));
  CHECK(et->getVelocity().x == doctest::Approx(0.5));
  CHECK(et->getVelocity().y == doctest::Approx(0));
}
 
TEST_CASE("Two boids, cohesion only")  //se messimo c>= o.5 si scambiano le posizioni
{
  Boid b1{{101.f, 101.f}, {0.f, 0.f}};
  Boid b2{{103.f, 101.f}, {1.f, 0.f}};
  std::vector birds{b1, b2};
  Parameters parameters{0.f, 0.5f, 4.f, 1.5f, 0.f};
  Flock flock{birds, parameters};
  flock.evolution();
  auto it = flock.flock().begin();
  auto et = it+1;
  CHECK(it->getPosition().x == doctest::Approx(102));
  CHECK(it->getPosition().y == doctest::Approx(101));
  CHECK(et->getPosition().x == doctest::Approx(103));
  CHECK(et->getPosition().y == doctest::Approx(101));

  CHECK(it->getVelocity().x == doctest::Approx(1));
  CHECK(it->getVelocity().y == doctest::Approx(0));
  CHECK(et->getVelocity().x == doctest::Approx(0));
  CHECK(et->getVelocity().y == doctest::Approx(0));
}

TEST_CASE("Two boids, alignment only: one still.")
{
  Boid b1{{101.f, 101.f}, {0.f, 1.f}};
  Boid b2{{102.f, 101.f}, {0.f, 0.f}};
  std::vector birds{b1, b2};
  Parameters parameters{0.5f, 0.f, 2.f, 1.5f, 0.f};
  Flock flock{birds, parameters};
  flock.evolution();
  auto it = flock.flock().begin();
  auto et = it+1;
  CHECK(it->getPosition().x == doctest::Approx(101));
  CHECK(it->getPosition().y == doctest::Approx(101.5));
  CHECK(et->getPosition().x == doctest::Approx(102));
  CHECK(et->getPosition().y == doctest::Approx(101.5));

  CHECK(it->getVelocity().x == doctest::Approx(0));
  CHECK(it->getVelocity().y == doctest::Approx(0.5f));
  CHECK(et->getVelocity().x == doctest::Approx(0));
  CHECK(et->getVelocity().y == doctest::Approx(0.5));
}

TEST_CASE("Overlap of two boids") //Come lo risolviamo?
{
  Boid b1{{101.f, 101.f}, {0.f, 1.f}};
  Boid b2{{101.f, 101.f}, {0.f, -1.f}};
  std::vector birds{b1, b2};
  Parameters parameters{0.5f, 0.5f, 2.f, 1.5f, 0.5f};
  Flock flock{birds, parameters};
  flock.evolution();
  auto it = flock.flock().begin();
  auto et = it+1;
  CHECK(et->getPosition().x == doctest::Approx(101));
  CHECK(et->getPosition().y == doctest::Approx(101));
  CHECK(et->getPosition().x == doctest::Approx(101));
  CHECK(et->getPosition().y == doctest::Approx(101));

  CHECK(et->getVelocity().x == doctest::Approx(0));
  CHECK(et->getVelocity().y == doctest::Approx(0));
  CHECK(et->getVelocity().x == doctest::Approx(0));
  CHECK(et->getVelocity().y == doctest::Approx(0));
}
} // namespace bd