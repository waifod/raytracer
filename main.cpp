#include <iostream>

#include "src/color.hpp"
#include "src/hittable.hpp"
#include "src/hittable_list.hpp"
#include "src/ray.hpp"
#include "src/sphere.hpp"
#include "src/vec3.hpp"

// Image
constexpr double ASPECT_RATIO{16.0 / 9.0};
constexpr int IMAGE_HEIGHT{800};

constexpr int getImageWidth() {
  auto width{int(double(IMAGE_HEIGHT) * ASPECT_RATIO)};
  return width < 1 ? 1 : width;
}
constexpr int IMAGE_WIDTH{getImageWidth()};

// Camera
constexpr double FOCAL_LENGTH{1.0};
constexpr double VIEWPORT_HEIGHT{2.0};
constexpr double VIEWPORT_WIDTH{VIEWPORT_HEIGHT *
                                (double(IMAGE_WIDTH) / IMAGE_HEIGHT)};
constexpr point CAMERA_CENTER{point(0, 0, 0)};

// Calculate the vectors across the horizontal and down the vertical
// viewport edges.
constexpr auto viewport_u{vec3(VIEWPORT_WIDTH, 0, 0)};
constexpr auto viewport_v{vec3(0, -VIEWPORT_HEIGHT, 0)};

// Calculate the horizontal and vertical delta vectors from pixel to pixel.
constexpr auto pixel_delta_u{viewport_u / IMAGE_WIDTH};
constexpr auto pixel_delta_v{viewport_v / IMAGE_HEIGHT};

// Calculate the location of the upper left pixel.
constexpr auto viewport_upper_left{CAMERA_CENTER - vec3(0, 0, FOCAL_LENGTH) -
                                   viewport_u / 2 - viewport_v / 2};
constexpr auto pixel00_loc{viewport_upper_left +
                           (pixel_delta_u + pixel_delta_v) / 2};

color ray_color(const ray& r, const hittable& world) {
  hit_record rec;
  if (world.hit(r, 0, std::numeric_limits<double>::infinity(), rec)) {
    return (rec.normal + color(1, 1, 1)) / 2;
  }

  auto unit_direction{r.direction().unit_vector()};
  auto a{(unit_direction.y() + 1.0) / 2};
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
  // World
  hittable_list world;
  world.add(std::make_shared<sphere>(point(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point(0, -100.5, -1), 100));

  // Render

  std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

  for (int j = 0; j < IMAGE_HEIGHT; j++) {
    std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' '
              << std::flush;
    for (int i = 0; i < IMAGE_WIDTH; i++) {
      auto pixel_center{pixel00_loc + i * pixel_delta_u + j * pixel_delta_v};
      auto ray_direction{pixel_center - CAMERA_CENTER};
      auto r{ray(CAMERA_CENTER, ray_direction)};

      auto pixel_color{ray_color(r, world)};
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\nDone.\n";
}
