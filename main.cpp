#include <iostream>

#include "src/camera.hpp"
#include "src/color.hpp"
#include "src/hittable.hpp"
#include "src/hittable_list.hpp"
#include "src/interval.hpp"
#include "src/ray.hpp"
#include "src/sphere.hpp"
#include "src/vec3.hpp"

int main() {
  hittable_list world;
  world.add(std::make_shared<sphere>(point(0, 0, -1), 0.5));
  world.add(std::make_shared<sphere>(point(0, -100.5, -1), 100));

  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);
}
