// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

// #include "statistics.hpp"
// #include "boid.hpp"
// #include "doctest.h"

// TEST_CASE("Vector functions")
// {
//   SUBCASE("Normalize function")
//   {
//     bd::Vector v{5, 0};
//     bd::normalize(v, 1);
//     CHECK(v.x == doctest::Approx(1));
//     CHECK(v.y == doctest::Approx(0));
//     // da aggiungere altri casi,  e test anche per le altre funzioni
//   }
// }

// TEST_CASE("Statistics functions")
// {
//   SUBCASE("doStatistics function throws with no entries")
//   {
//     std::vector<double> v;
//     CHECK_THROWS(bd::doStatistics(v));
//   }

//   SUBCASE("doStatistics function throws with just one entry")
//   {
//     std::vector v{1.};
//     CHECK_THROWS(bd::doStatistics(v));
//   }

//   SUBCASE("doStatistics function for two entries")
//   {
//     std::vector v{1., 2.};
//     const auto result = bd::doStatistics(v);
//     CHECK(result.mean == doctest::Approx(1.5));
//     CHECK(result.sigma == doctest::Approx(0.70710678));
//   }

//   SUBCASE("doStatistics function for five entries")
//   {
//     std::vector v{1.5, 2., 2.5, 3., 3.5};
//     const auto result = bd::doStatistics(v);
//     CHECK(result.mean == doctest::Approx(2.5));
//     CHECK(result.sigma == doctest::Approx(0.79056942));
//   }

//   SUBCASE("Binomial coefficients")
//   {
//     double n{6};
//     double k{3};
//     auto result{bd::binomialCoeff(n, k)};
//     CHECK(result == doctest::Approx(20));
//   }
// }

// TEST_CASE("Statistics function for flocks")
// {
//   SUBCASE("statistics function throws for two boids")
//   {
//     bd::Boid b1{{0.f, 0.f}, {4.f, 3.f}};
//     bd::Boid b2{{0.f, 2.f}, {12.f, 5.f}};
//     std::vector birds{b1, b2};
//     bd::Flock f{birds, bd::Parameters{}};
//     CHECK_THROWS(statistics(f));
//   }

//   SUBCASE("statistics function for three boids")
//   {
//     bd::Boid b1{{0.f, 0.f}, {4.f, 3.f}};
//     bd::Boid b2{{0.f, 2.f}, {12.f, 5.f}};
//     bd::Boid b3{{1.f, 0.f}, {24.f, 7.f}};
//     std::vector birds{b1, b2, b3};
//     bd::Flock f{birds, bd::Parameters{}};
//     bd::Results results = statistics(f);
//     CHECK(results.speedStats.mean == doctest::Approx(14.33333333));
//     CHECK(results.speedStats.sigma == doctest::Approx(10.06644591));
//     CHECK(results.distanceStats.mean == doctest::Approx(1.745355993));
//     CHECK(results.distanceStats.sigma == doctest::Approx(0.6562001899));
//   }
// }