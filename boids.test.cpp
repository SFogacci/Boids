#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "boid.hpp"
#include "doctest.h"

TEST_CASE("One boid, all rules")
{
  bd::Boid b1{{101.f, 101.f}, {1.f, 1.f}};
  std::vector birds{b1};
  bd::Parameters parameters{0.5f, 0.5f, 2.f, 1.5f, 0.5f, 2};
  bd::Flock flock{birds, parameters};
  bd::Boid predator{{500.f, 500.f}, {}, 1};

  flock.evolution(predator);
  auto it = flock.getFlock().begin();
  CHECK(it->getPosition().x == doctest::Approx(102.f));
  CHECK(it->getPosition().y == doctest::Approx(102.f));

  CHECK(it->getVelocity().x == doctest::Approx(1.f));
  CHECK(it->getVelocity().y == doctest::Approx(1.f));
}

TEST_CASE("Two Boids, separation only")
{
  bd::Boid b1{{101.f, 101.f}, {}};
  bd::Boid b2{{102.f, 101.f}, {}};
  std::vector birds{b1, b2};
  bd::Parameters parameters{0.f, 0.f, 1.f, 20.f, 2.f, 2};
  bd::Flock flock{birds, parameters};
  bd::Boid predator{{500.f, 500.f}, {}, 1};
  flock.evolution(predator);
  auto it = flock.getFlock().begin();
  auto et = it + 1;
  CHECK(it->getPosition().x == doctest::Approx(99.f));
  CHECK(it->getPosition().y == doctest::Approx(101.f));
  CHECK(et->getPosition().x == doctest::Approx(104.f));
  CHECK(et->getPosition().y == doctest::Approx(101.f));

  CHECK(it->getVelocity().x == doctest::Approx(-2.f));
  CHECK(it->getVelocity().y == doctest::Approx(0.f));
  CHECK(et->getVelocity().x == doctest::Approx(2.f));
  CHECK(et->getVelocity().y == doctest::Approx(0.f));
}

TEST_CASE("Two Boids, cohesion only")
{
  bd::Boid b1{{101.f, 101.f}, {}};
  bd::Boid b2{{103.f, 101.f}, {1.f, 0.f}};
  std::vector birds{b1, b2};
  bd::Parameters parameters{0.5f, 0.f, 0.f, 4.f, 1.5f, 2};
  bd::Flock flock{birds, parameters};
  bd::Boid predator{{500.f, 500.f}, {}, 1};
  flock.evolution(predator);
  auto it = flock.getFlock().begin();
  auto et = it + 1;
  CHECK(it->getPosition().x == doctest::Approx(102.f));
  CHECK(it->getPosition().y == doctest::Approx(101.f));
  CHECK(et->getPosition().x == doctest::Approx(103.f));
  CHECK(et->getPosition().y == doctest::Approx(101.f));

  CHECK(it->getVelocity().x == doctest::Approx(1.f));
  CHECK(it->getVelocity().y == doctest::Approx(0.f));
  CHECK(et->getVelocity().x == doctest::Approx(0.f));
  CHECK(et->getVelocity().y == doctest::Approx(0.f));
}

TEST_CASE("Two boids, alignment only: one still.")
{
  bd::Boid b1{{101.f, 101.f}, {0.f, 1.f}};
  bd::Boid b2{{102.f, 101.f}, {}};
  std::vector birds{b1, b2};
  bd::Parameters parameters{0.f, 0.5f, 0.f, 2.f, 1.5f, 2};
  bd::Flock flock{birds, parameters};
  bd::Boid predator{{500.f, 500.f}, {}, 1};
  flock.evolution(predator);
  auto it = flock.getFlock().begin();
  auto et = it + 1;
  CHECK(it->getPosition().x == doctest::Approx(101.f));
  CHECK(it->getPosition().y == doctest::Approx(101.5f));
  CHECK(et->getPosition().x == doctest::Approx(102.f));
  CHECK(et->getPosition().y == doctest::Approx(101.5f));
  CHECK(it->getVelocity().x == doctest::Approx(0.f));
  CHECK(it->getVelocity().y == doctest::Approx(0.5f));
  CHECK(et->getVelocity().x == doctest::Approx(0.f));
  CHECK(et->getVelocity().y == doctest::Approx(0.5f));
}

TEST_CASE("Overlap of two boids")
{
  bd::Boid b1{{101.f, 100.f}, {0.f, 1.f}};
  bd::Boid b2{{101.f, 102.f}, {0.f, -1.f}};
  std::vector birds{b1, b2};
  bd::Parameters parameters{0.f, 0.f, 0.f, 0.f, 0.f, 2};
  bd::Flock flock{birds, parameters};
  bd::Boid predator{{500.f, 500.f}, {}, 1};
  flock.evolution(predator);
  auto it = flock.getFlock().begin();
  auto et = it + 1;
  CHECK(it->getPosition().x == doctest::Approx(101.f));
  CHECK(it->getPosition().y == doctest::Approx(101.f));
  CHECK(it->getVelocity().x == doctest::Approx(0.f));
  CHECK(it->getVelocity().y == doctest::Approx(1.f));

  CHECK(!(*it == *et));
}

TEST_CASE("Two boids, usual situation")
{
  SUBCASE("No interaction")
  {
    bd::Boid b1{{101.f, 101.f}, {2.f, -1.f}};
    bd::Boid b2{{105.f, 90.f}, {-2.f, 3.f}};
    std::vector birds{b1, b2};
    bd::Parameters parameters{0.5f, 0.5f, 0.5f, 10.f, 1.f, 2};
    bd::Flock flock{birds, parameters};
    bd::Boid predator{{500.f, 500.f}, {}, 1};
    flock.evolution(predator);
    auto it = flock.getFlock().begin();
    auto et = it + 1;

    CHECK(it->getPosition().x == doctest::Approx(103.f));
    CHECK(it->getPosition().y == doctest::Approx(100.f));
    CHECK(et->getPosition().x == doctest::Approx(103.f));
    CHECK(et->getPosition().y == doctest::Approx(93.f));
    CHECK(it->getVelocity().x == doctest::Approx(2.f));
    CHECK(it->getVelocity().y == doctest::Approx(-1.f));
    CHECK(et->getVelocity().x == doctest::Approx(-2.f));
    CHECK(et->getVelocity().y == doctest::Approx(3.f));
  }

  SUBCASE("All rules")
  {
    bd::Boid b1{{101.f, 101.f}, {2.f, -1.f}};
    bd::Boid b2{{105.f, 98.f}, {-2.f, 5.f}};
    std::vector birds{b1, b2};
    bd::Parameters parameters{0.5f, 0.5f, 0.5f, 20.f, 10.f, 2};
    bd::Flock flock{birds, parameters};
    bd::Boid predator{{500.f, 500.f}, {}, 1};
    flock.evolution(predator);
    auto it1 = flock.getFlock().begin();
    auto et1 = it1 + 1;

    CHECK(it1->getPosition().x == doctest::Approx(102.2f));
    CHECK(it1->getPosition().y == doctest::Approx(102.1f));
    CHECK(et1->getPosition().x == doctest::Approx(103.8f));
    CHECK(et1->getPosition().y == doctest::Approx(100.9f));

    CHECK(it1->getVelocity().x == doctest::Approx(1.2f));
    CHECK(it1->getVelocity().y == doctest::Approx(1.1f));
    CHECK(et1->getVelocity().x == doctest::Approx(-1.2f));
    CHECK(et1->getVelocity().y == doctest::Approx(2.9f));
  }
}

TEST_CASE("Testing toroidalDifference function")
{
  bd::Vector pos1{100.0f, 100.0f};
  bd::Vector pos2{700.0f, 500.0f};
  bd::Vector result = toroidalDifference(pos1, pos2);
  CHECK(result.x == doctest::Approx(200.0f));
  CHECK(result.y == doctest::Approx(200.0f));

  pos1   = {700.0f, 500.0f};
  pos2   = {100.0f, 100.0f};
  result = toroidalDifference(pos1, pos2);
  CHECK(result.x == doctest::Approx(-200.0f));
  CHECK(result.y == doctest::Approx(-200.0f));

  pos1   = {400.0f, 300.0f};
  pos2   = {400.0f, 100.0f};
  result = toroidalDifference(pos1, pos2);
  CHECK(result.x == doctest::Approx(0.0f));
  CHECK(result.y == doctest::Approx(200.0f));

  pos1   = {0.0f, 0.0f};
  pos2   = {400.0f, 300.0f};
  result = toroidalDifference(pos1, pos2);
  CHECK(result.x == doctest::Approx(-400.0f));
  CHECK(result.y == doctest::Approx(-300.0f));

  pos1   = {0.0f, 0.0f};
  pos2   = {800.0f, 600.0f};
  result = toroidalDifference(pos1, pos2);
  CHECK(result.x == doctest::Approx(0.0f));
  CHECK(result.y == doctest::Approx(0.0f));

  pos1   = {0.0f, 0.0f};
  pos2   = {0.0f, 0.0f};
  result = toroidalDifference(pos1, pos2);
  CHECK(result.x == doctest::Approx(0.0f));
  CHECK(result.y == doctest::Approx(0.0f));
}

TEST_CASE("Testing Boid::hasNeighbour function")
{
  bd::Boid boid1({100.0f, 100.0f}, {});
  bd::Boid boid2({700.0f, 500.0f}, {});
  bd::Boid boid3({400.0f, 500.0f}, {});
  bd::Boid boid4({100.0f, 100.0f}, {});
  bd::Boid boid5({300.0f, 300.0f}, {});

  SUBCASE("Neighbours in toroidal distance")
  {
    CHECK(boid1.hasNeighbour(boid2, 300.0f) == true);
  }

  SUBCASE("Neighbours in normal distance")
  {
    CHECK(boid1.hasNeighbour(boid5, 300.0f) == true);
  }

  SUBCASE("Boids far from each other")
  {
    CHECK(boid1.hasNeighbour(boid5, 200.0f) == false);
  }

  SUBCASE("Overlapped boids")
  {
    CHECK(boid1.hasNeighbour(boid4, 1.0f) == true);
  }

  SUBCASE("Same boid")
  {
    CHECK(boid1.hasNeighbour(boid1, 1.0f) == false);
  }

  SUBCASE("Limiting case")
  {
    CHECK(boid1.hasNeighbour(boid3, 500.0f) == true);
  }
}

TEST_CASE("Testing normalize function")
{
  bd::Vector v;
  float f;

  SUBCASE("Normalizing a non-zero vector")
  {
    v = {3.0f, 4.0f};
    f = 10.0f;
    normalize(v, f);
    CHECK(v.x == doctest::Approx(6.0f));
    CHECK(v.y == doctest::Approx(8.0f));
  }

  SUBCASE("Normalizing a zero vector")
  {
    v = {0.0f, 0.0f};
    f = 10.0f;
    normalize(v, f);
    CHECK(v.x == doctest::Approx(0.0f));
    CHECK(v.y == doctest::Approx(0.0f));
  }

  SUBCASE("Normalizing a negative vector")
  {
    v = {-3.0f, -4.0f};
    f = 10.0f;
    normalize(v, f);
    CHECK(v.x == doctest::Approx(-6.0f));
    CHECK(v.y == doctest::Approx(-8.0f));
  }
}

TEST_CASE("Testing Boid::correctBorders function")
{
  SUBCASE("Boid inside the window")
  {
    bd::Boid boid({400.0f, 300.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(400.0f));
    CHECK(boid.getPosition().y == doctest::Approx(300.0f));
  }

  SUBCASE("Boid outside the right border")
  {
    bd::Boid boid({850.0f, 300.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(50.0f));
    CHECK(boid.getPosition().y == doctest::Approx(300.0f));
  }

  SUBCASE("Boid outside the left border")
  {
    bd::Boid boid({-50.0f, 300.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(750.0f));
    CHECK(boid.getPosition().y == doctest::Approx(300.0f));
  }

  SUBCASE("Boid outside the top border")
  {
    bd::Boid boid({400.0f, 650.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(400.0f));
    CHECK(boid.getPosition().y == doctest::Approx(50.0f));
  }

  SUBCASE("Boid outside the bottom border")
  {
    bd::Boid boid({400.0f, -50.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(400.0f));
    CHECK(boid.getPosition().y == doctest::Approx(550.0f));
  }

  SUBCASE("Boid on the right border")
  {
    bd::Boid boid({800.0f, 300.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(800.0f));
    CHECK(boid.getPosition().y == doctest::Approx(300.0f));
  }

  SUBCASE("Boid on the left border")
  {
    bd::Boid boid({0.0f, 300.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(0.0f));
    CHECK(boid.getPosition().y == doctest::Approx(300.0f));
  }

  SUBCASE("Boid on the top border")
  {
    bd::Boid boid({400.0f, 600.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(400.0f));
    CHECK(boid.getPosition().y == doctest::Approx(600.0f));
  }

  SUBCASE("Boid on the bottom border")
  {
    bd::Boid boid({400.0f, 0.0f}, {});
    boid.correctBorders();
    CHECK(boid.getPosition().x == doctest::Approx(400.0f));
    CHECK(boid.getPosition().y == doctest::Approx(0.0f));
  }
}

TEST_CASE("Testing predator-boid interaction")
{
  SUBCASE("No interaction")
  {
    bd::Boid b1{{101.f, 101.f}, {2.f, -1.f}};
    std::vector birds{b1};
    bd::Parameters parameters{0.5f, 0.5f, 0.5f, 10.f, 1.f, 1};
    bd::Flock flock{birds, parameters};
    bd::Boid predator{{200.f, 200.f}, {3.f, 2.f}, 1};
    predator.predatorEvolution(flock);
    flock.evolution(predator);
    auto it = flock.getFlock().begin();

    CHECK(it->getPosition().x == doctest::Approx(103.f));
    CHECK(it->getPosition().y == doctest::Approx(100.f));
    CHECK(predator.getPosition().x == doctest::Approx(200.f));
    CHECK(predator.getPosition().y == doctest::Approx(200.f));
    CHECK(it->getVelocity().x == doctest::Approx(2.f));
    CHECK(it->getVelocity().y == doctest::Approx(-1.f));
    CHECK(predator.getVelocity().x == doctest::Approx(3.f));
    CHECK(predator.getVelocity().y == doctest::Approx(2.f));
  }

  SUBCASE("All rules")
  {
    bd::Boid b1{{101.f, 101.f}, {2.f, -1.f}};
    std::vector birds{b1};
    bd::Parameters parameters{0.5f, 0.5f, 0.5f, 10.f, 1.f, 1};
    bd::Flock flock{birds, parameters};
    bd::Boid predator{{100.f, 100.f}, {3.f, 2.f}, 1};
    bd::Boid predator_ev{{100.f, 100.f}, {3.f, 2.f}, 1};
    predator_ev = predator.predatorEvolution(flock);
    flock.evolution(predator);
    auto it = flock.getFlock().begin();

    CHECK(it->getPosition().x == doctest::Approx(103.5f));
    CHECK(it->getPosition().y == doctest::Approx(100.5f));
    CHECK(predator_ev.getPosition().x == doctest::Approx(104.f));
    CHECK(predator_ev.getPosition().y == doctest::Approx(103.f));
    CHECK(it->getVelocity().x == doctest::Approx(2.5f));
    CHECK(it->getVelocity().y == doctest::Approx(-0.5f));
    CHECK(predator_ev.getVelocity().x == doctest::Approx(4.f));
    CHECK(predator_ev.getVelocity().y == doctest::Approx(3.f));
  }
}

TEST_CASE("Testing Boid::biologicalLimits function")
{
  bd::Boid b1{{100.f, 100.f}, {6.f, 8.f}};
  std::vector birds{b1};
  bd::Parameters parameters{0.5f, 0.5f, 0.5f, 20.f, 10.f, 2};
  bd::Flock flock{birds, parameters};
  bd::Boid predator{{500.f, 500.f}, {}, 1};
  flock.evolution(predator);
  auto it1 = flock.getFlock().begin();

  CHECK(it1->getPosition().x == doctest::Approx(103.f));
  CHECK(it1->getPosition().y == doctest::Approx(104.f));

  CHECK(it1->getVelocity().x == doctest::Approx(3.f));
  CHECK(it1->getVelocity().y == doctest::Approx(4.f));
}