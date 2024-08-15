#ifndef UTILS_H
#define UTILS_H

#include <limits>
#include <numbers>
#include <random>

constexpr double infty = std::numeric_limits<double>::infinity();
constexpr double pi = std::numbers::pi;

constexpr double degrees_to_radians(double degrees) {
  return degrees * pi;
}

// Returns a random real in [0,1).
inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

// Returns a random real in [min,max).
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

#endif