#include "color.hpp"

#include <iostream>

#include "interval.hpp"

void write_color(std::ostream& out, const color& pixel_color) {
  auto r{pixel_color.x()};
  auto g{pixel_color.y()};
  auto b{pixel_color.z()};

  static constexpr auto intensity {interval(0, 0.999)};
  int rbyte{int(256 * intensity.clamp(r))};
  int gbyte{int(256 * intensity.clamp(g))};
  int bbyte{int(256 * intensity.clamp(b))};
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
