#ifndef HITTABLE_H
#define HITTABLE_H

#include "interval.hpp"
#include "ray.hpp"

struct hit_record {
  point p;
  vec3 normal;
  double t;
  bool front_face;

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
                   hit_record& rec) const = 0;
};

#endif
