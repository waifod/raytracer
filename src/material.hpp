#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.hpp"
#include "hittable.hpp"
#include "utils.hpp"
#include "vec3.hpp"

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
    if (scatter_direction.near_zero()) [[unlikely]]
      scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }

 private:
  color albedo;
};

class metal : public material {
 public:
  explicit metal(const color& albedo, double fuzz)
      : albedo{albedo}, fuzz{fuzz} {}

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
               ray& scattered) const noexcept override {
    auto reflected = reflect(r_in.direction(), rec.normal) +
                     fuzz * vec3::random_unit_vector();
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return dot(scattered.direction(), rec.normal) > 0;
  }

 private:
  color albedo;
  double fuzz;
};

class dielectric : public material {
 public:
  explicit dielectric(double refraction_index) noexcept
      : refraction_index{refraction_index} {}

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
               ray& scattered) const noexcept override {
    attenuation = color{1.0, 1.0, 1.0};
    auto ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

    auto unit_direction = r_in.direction().unit_vector();
    auto cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    auto sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    auto cannot_refract = ri * sin_theta > 1.0;
    auto direction =
        cannot_refract || reflectance(cos_theta, ri) > random_double()
            ? reflect(unit_direction, rec.normal)
            : refract(unit_direction, rec.normal, ri);

    scattered = ray(rec.p, direction);
    return true;
  }

 private:
  // Refractive index in vacuum or air, or the ratio of the material's
  // refractive index over the refractive index of the enclosing media
  double refraction_index;

  static double reflectance(double cosine, double refraction_index) noexcept {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
  }
};

#endif
