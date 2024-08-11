#include <iostream>

#include "src/camera.hpp"
#include "src/color.hpp"
#include "src/hittable.hpp"
#include "src/hittable_list.hpp"
#include "src/interval.hpp"
#include "src/ray.hpp"
#include "src/sphere.hpp"
#include "src/vec3.hpp"

// Image
constexpr double ASPECT_RATIO{16.0 / 9.0};
constexpr int IMAGE_WIDTH{400};

int main() {
  // World
  hittable_list world;
  world.add(std::make_shared<sphere>(point(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point(0, -100.5, -1), 100));

  // Camera settings
  camera cam;
  cam.aspect_ratio = ASPECT_RATIO;
  cam.image_width = IMAGE_WIDTH;

  cam.render(world);
}
