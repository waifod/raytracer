#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>

#include "interval.hpp"
#include "ray.hpp"

class material;

struct hit_record {
  bool front_face;
  point p;
  vec3 normal;
  double t;
  material* mat;

  // Set the hit record normal vector.
  // NOTE: the parameter output_normal is assumed to be normalized.
  void set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
 public:
  virtual ~hittable() = default;

  virtual bool hit(const ray& r, interval ray_t,
                   hit_record& rec) const noexcept = 0;
};

#endif
