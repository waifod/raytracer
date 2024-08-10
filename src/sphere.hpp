#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"

class sphere : public hittable {
  public:
    explicit sphere(const point& center, double radius) noexcept;
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const noexcept override;

  private:
    point center;
    double radius;
};

#endif
