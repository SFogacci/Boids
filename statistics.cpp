#include "statistics.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>

namespace bd {

double binomialCoeff(double n, double k)
{
  assert(n > 0 && k > 0);
  return 1 / ((n + 1) * std::beta(n - k + 1, k + 1));
}

Stats doStatistics(std::vector<double> const& entries)
{
  const int N{static_cast<int>(entries.size())};
  if (N < 2) {
    throw std::runtime_error{"Not enough entries to run a statistics"};
  }

  const auto sum_entries = std::reduce(entries.begin(), entries.end(), 0.);
  const auto mean{sum_entries / N};

  const auto squared_devs = std::accumulate(
      entries.begin(), entries.end(), 0., [mean](auto sum, auto const& entry) {
        return sum += std::pow(entry - mean, 2);
      });
  const auto sigma{std::sqrt(squared_devs / (N - 1))};

  return {mean, sigma};
}

Results statistics(Flock const& f)
{
  const auto flock{f.getFlock()};
  const auto N{flock.size()};
  // assert(N >= 3); // otherwise there would be just one distance, so stats
  // could not be computed

  std::vector<double> speeds;
  std::vector<double> distances;
  speeds.reserve(N);
  const auto pairs{binomialCoeff(static_cast<double>(N), 2.)};
  distances.reserve(
      static_cast<std::size_t>(pairs)); // conversions are to be improved

  for (std::size_t i = 0; i < N; ++i) {
    auto velocity = flock[i].getVelocity();
    speeds.push_back(norm(velocity)); // filling the speeds vector with the
                                      // magnitude of each boid's velocity
    for (std::size_t j = i + 1; j < N; ++j) {
      auto distance = flock[i].getPosition() - flock[j].getPosition();
      distances.push_back(norm(distance));
    } // filling the distances vector with the distance of each pair of boids
  }

  const Stats speedStats{doStatistics(speeds)};
  const Stats distanceStats{doStatistics(distances)};

  return Results{speedStats, distanceStats};
}
} // namespace bd