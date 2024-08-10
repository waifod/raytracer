#include "hittable.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

sphere::sphere(const point& center, double radius) noexcept
: center{center}
, radius{(std::fmax(0,radius))} {}

bool sphere::hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const noexcept {
  auto oc_dir{center - r.origin()};
  auto a{r.direction().norm_squared()};
  auto h{dot(r.direction(), oc_dir)};
  auto c{oc_dir.norm_squared() - radius * radius};
  auto discriminant{h * h - a * c};

  if (discriminant < 0) {
    return false;
  }
  
  auto sqrtd {std::sqrt(discriminant)};
  auto root {(h - sqrtd) / a};
  if (root <= ray_tmin || ray_tmax <= root) {
    root = (h+sqrtd)/a;
    if (root <= ray_tmin || ray_tmax <= root) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  auto outward_normal {(rec.p-center)/radius};
  rec.set_face_normal(r, outward_normal);

  return true;
}

