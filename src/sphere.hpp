#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "hittable.hpp"
#include "interval.hpp"
#include "vec3.hpp"

class sphere : public hittable {
 public:
  [[nodiscard]] explicit sphere(const point& center, double radius,
                                std::shared_ptr<material> mat) noexcept;
  [[nodiscard]] bool hit(const ray& r, interval ray_t,
                         hit_record& rec) const noexcept override;

 private:
  point center;
  double radius;
  std::shared_ptr<material> mat;
};

#endif
