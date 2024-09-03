#include "camera.hpp"

#include <ios>

#include "color.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vec3.hpp"

void camera::render(const hittable& world) {
  initialize();

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << image_height - j << ' '
              << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto pixel_color{color(0, 0, 0)};
      for (auto sample{0}; sample < samples_per_pixel; ++sample) {
        auto r{get_ray(i, j)};
        pixel_color += ray_color(r, max_depth, world);
      }
      write_color(std::cout, pixel_samples_scale * pixel_color);
    }
  }

  std::clog << "\rDone.                 \n";
}

void camera::initialize() {
  // Needed to avoid syncing cout with the stdout from the C stdio library.
  std::ios_base::sync_with_stdio(false);

  image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  pixel_samples_scale = 1.0 / samples_per_pixel;

  center = lookfrom;

  // Determine viewport dimensions.
  auto theta = degrees_to_radians(vfov);
  auto h = std::tan(theta / 2);
  auto viewport_height = 2 * h * focus_dist;
  auto viewport_width = viewport_height * (double(image_width) / image_height);

  // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
  w = (lookfrom - lookat).unit_vector();
  u = cross(vup, w).unit_vector();
  v = cross(w, u);

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  auto viewport_u =
      viewport_width * u;  // Vector across viewport horizontal edge
  auto viewport_v = -viewport_height * v;  // Vector down viewport vertical edge

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  pixel_delta_u = viewport_u / image_width;
  pixel_delta_v = viewport_v / image_height;

  // Calculate the location of the upper left pixel.
  auto viewport_upper_left =
      center - focus_dist * w - viewport_u / 2 - viewport_v / 2;
  pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Calculate the camera defocus disk basis vectors.
  auto defocus_radius =
      focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
  defocus_disk_u = u * defocus_radius;
  defocus_disk_v = v * defocus_radius;
}

color camera::ray_color(const ray& r, int depth, const hittable& world) const {
  // If we've exceeded the ray bounce limit, no more light is gathered.
  if (depth == 0) {
    return color(0, 0, 0);
  }

  hit_record rec;
  if (world.hit(r, interval(0.001, infty), rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, --depth, world);
    return color{0, 0, 0};
  }

  auto unit_direction{r.direction().unit_vector()};
  auto a{(unit_direction.y() + 1.0) / 2};
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

// Construct a camera ray originating from the origin and directed at
// a randomly sampled point around the pixel location i, j.
ray camera::get_ray(int i, int j) const noexcept {
  // Construct a camera ray originating from the defocus disk and directed at a
  // randomly sampled point around the pixel location i, j.
  auto offset{sample_square()};
  auto pixel_sample{pixel00_loc + ((i + offset.x()) * pixel_delta_u) +
                    ((j + offset.y()) * pixel_delta_v)};
  auto ray_origin = defocus_angle < 0 ? center : defocus_disk_sample();
  auto ray_direction{pixel_sample - ray_origin};
  return ray(ray_origin, ray_direction);
}

// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
vec3 camera::sample_square() const noexcept {
  return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

point camera::defocus_disk_sample() const noexcept {
  auto p = vec3::random_in_unit_disk();
  return center + p.x() * defocus_disk_u + p.y() * defocus_disk_v;
}
