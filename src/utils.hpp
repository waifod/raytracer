#include <numbers>

constexpr double degrees_to_radians(double degrees) {
  return degrees * std::numbers::pi;
}
