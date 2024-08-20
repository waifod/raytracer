#ifndef CAMERA_H
#define CAMERA_H

#include "color.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class camera {
 public:
  double aspect_ratio = 1.0;   // Ratio of image width over height
  int image_width = 100;       // Rendered image width in pixel count
  int samples_per_pixel = 10;  // Count of random samples for each pixel
  int max_depth = 10;          // Maximum number of ray bounces into scene

  [[nodiscard]] explicit camera() = default;
  void render(const hittable& world);

 private:
  // NOTE: we can keep image_height first because
  //  it does not impact the size of this class.
  int image_height;            // Rendered image height
  double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
  point center;                // Camera center
  point pixel00_loc;           // Location of pixel 0, 0
  vec3 pixel_delta_u;          // Offset to pixel to the right
  vec3 pixel_delta_v;          // Offset to pixel below

  void initialize();
  color ray_color(const ray& r, int depth, const hittable& world) const;
  ray get_ray(int i, int j) const noexcept;
  vec3 sample_square() const noexcept;
};

#endif