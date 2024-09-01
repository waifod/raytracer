#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.hpp"
#include "hittable.hpp"

class material {
 public:
  virtual ~material() = default;

  virtual bool scatter(const ray& r_in, const hit_record& rec,
                       color& attenuation, ray& scattered) const noexcept {
    return false;
  }
};

class lambertian : public material {
 public:
  explicit lambertian(const color& albedo) : albedo{albedo} {}

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
               ray& scattered) const noexcept override {
    auto scatter_direction = rec.normal + vec3::random_unit_vector();
    if (scatter_direction.near_zero()) scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

 private:
  color albedo;
};

class metal : public material {
 public:
  explicit metal(const color& albedo) : albedo{albedo} {}

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
               ray& scattered) const noexcept override {
    auto reflected = reflect(r_in.direction(), rec.normal);
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
  }

 private:
  color albedo;
};

#endif
