#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "boid.hpp"

namespace bd {
struct Stats
{
  double mean;
  double sigma;
};

struct Results
{
  Stats speedStats;
  Stats distanceStats;
};

double binomialCoeff(double, double);

Stats doStatistics(std::vector<double> const&);

Results statistics(Flock const&);
} // namespace bd

#endif