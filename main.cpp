#include <memory>

#include "src/camera.hpp"
#include "src/color.hpp"
#include "src/hittable_list.hpp"
#include "src/material.hpp"
#include "src/sphere.hpp"
#include "src/utils.hpp"
#include "src/vec3.hpp"

int main() {
  hittable_list world;

  auto ground_material = std::make_unique<lambertian>(color{0.5, 0.5, 0.5});
  world.add(std::make_unique<sphere>(point{0, -1000, 0}, 1000,
                                     std::move(ground_material)));

  for (int a{-11}; a < 11; ++a) {
    for (int b{-11}; b < 11; ++b) {
      auto choose_mat = random_double();
      point center{a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};

      if ((center - point(4, 0.2, 0)).norm() > 0.9) {
        std::unique_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = color::random() * color::random();
          sphere_material = std::make_unique<lambertian>(albedo);
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = std::make_unique<metal>(albedo, fuzz);
        } else {
          // glass
          sphere_material = std::make_unique<dielectric>(1.5);
        }
        world.add(
            std::make_unique<sphere>(center, 0.2, std::move(sphere_material)));
      }
    }
  }

  auto material1 = std::make_unique<dielectric>(1.5);
  world.add(
      std::make_unique<sphere>(point{0, 1, 0}, 1.0, std::move(material1)));

  auto material2 = std::make_unique<lambertian>(color{0.4, 0.2, 0.1});
  world.add(
      std::make_unique<sphere>(point{-4, 1, 0}, 1.0, std::move(material2)));

  auto material3 = std::make_unique<metal>(color{0.7, 0.6, 0.5}, 0.0);
  world.add(
      std::make_unique<sphere>(point{4, 1, 0}, 1.0, std::move(material3)));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;  // 500
  cam.max_depth = 50;           // 50

  cam.vfov = 20;
  cam.lookfrom = point{13, 2, 3};
  cam.lookat = point{0, 0, 0};
  cam.vup = vec3{0, 1, 0};

  cam.defocus_angle = 0.6;
  cam.focus_dist = 10.0;

  cam.render(world);
}
