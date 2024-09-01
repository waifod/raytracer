#include "src/camera.hpp"
#include "src/color.hpp"
#include "src/hittable_list.hpp"
#include "src/material.hpp"
#include "src/sphere.hpp"
#include "src/vec3.hpp"

int main() {
  hittable_list world;

  auto material_ground = std::make_shared<lambertian>(color{0.8, 0.8, 0.0});
  auto material_center = std::make_shared<lambertian>(color{0.1, 0.2, 0.5});
  auto material_left = std::make_shared<dielectric>(1.5);
  auto material_bubble = std::make_shared<dielectric>(1.0 / 1.5);
  auto material_right = std::make_shared<metal>(color{0.8, 0.6, 0.2}, 1.0);

  world.add(std::make_shared<sphere>(point{0.0, -100.5, -1.0}, 100.0,
                                     material_ground));
  world.add(
      std::make_shared<sphere>(point{0.0, 0, -1.2}, 0.5, material_center));
  world.add(
      std::make_shared<sphere>(point(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(
      std::make_shared<sphere>(point(-1.0, 0.0, -1.0), 0.4, material_bubble));
  world.add(
      std::make_shared<sphere>(point(1.0, 0.0, -1.0), 0.5, material_right));

  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);
}
