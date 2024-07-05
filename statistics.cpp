#include "statistics.hpp"
#include "vectors.hpp"
#include <cassert>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <sstream>
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
    throw std::runtime_error{"Not enough entries to run a statistics."};
  }

  const auto sumEntries = std::reduce(entries.begin(), entries.end(), 0.);
  const auto mean{sumEntries / N};

  const auto squaredDevs = std::accumulate(
      entries.begin(), entries.end(), 0., [mean](auto sum, auto const& entry) {
        return sum += std::pow(entry - mean, 2);
      });
  const auto sigma{std::sqrt(squaredDevs / (N - 1))};

  return {mean, sigma};
}

Results statistics(Flock const& f)
{
  const auto flock{f.getFlock()};
  const auto N{flock.size()};

  std::vector<double> speeds;
  std::vector<double> distances;
  speeds.reserve(N);
  const auto pairs{binomialCoeff(static_cast<double>(N), 2.)};
  distances.reserve(static_cast<std::size_t>(pairs));

  for (std::size_t i = 0; i != N; ++i) {
    auto velocity = flock[i].getVelocity();
    speeds.push_back(norm(velocity));
    for (std::size_t j = i + 1; j < N; ++j) {
      auto distance =
          toroidalDifference(flock[i].getPosition(), flock[j].getPosition());
      distances.push_back(norm(distance));
    }
  }

  const Stats speedStats{doStatistics(speeds)};
  const Stats distanceStats{doStatistics(distances)};

  return Results{speedStats, distanceStats};
}

std::string printStatistics(Results const& results)
{
  const std::string print{
      "Flock mean speed: " + std::to_string(results.speedStats.mean) + '\n'
      + "Flock speed standard deviation: "
      + std::to_string(results.speedStats.sigma) + '\n'
      + "Flock mean distance: " + std::to_string(results.distanceStats.mean)
      + '\n' + "Flock distance standard deviation: "
      + std::to_string(results.distanceStats.sigma) + '\n' + '\n'};
  return print;
}

std::string fileName()
{
  auto timeNow      = std::chrono::system_clock::now();
  auto timeNowTimeT = std::chrono::system_clock::to_time_t(timeNow);

  std::stringstream t;
  t << std::put_time(std::localtime(&timeNowTimeT), "%Y_%m_%d_%X");
  return "statistics_" + t.str() + ".pdf";
}
} // namespace bd