#ifndef VEC3_H
#define VEC3_H

#include <array>
#include <cmath>
#include <iostream>

#include "utils.hpp"

class vec3 {
 private:
  std::array<double, 3> m_c{0, 0, 0};

 public:
  [[nodiscard]] constexpr explicit vec3() noexcept = default;
  [[nodiscard]] constexpr explicit vec3(double x, double y, double z) noexcept
      : m_c{x, y, z} {}

  [[nodiscard]] static inline vec3 random() {
    return vec3{random_double(), random_double(), random_double()};
  }
  [[nodiscard]] static inline vec3 random(double min, double max) {
    return vec3{random_double(min, max), random_double(min, max),
                random_double(min, max)};
  }
  [[nodiscard]] static inline vec3 random_in_unit_sphere() {
    return vec3::random(-1, 1) / std::sqrt(3);
  }
  [[nodiscard]] static inline vec3 random_unit_vector() {
    return vec3::random().unit_vector();
  }

  [[nodiscard]] constexpr double x() const noexcept { return m_c[0]; }
  [[nodiscard]] constexpr double y() const noexcept { return m_c[1]; }
  [[nodiscard]] constexpr double z() const noexcept { return m_c[2]; }

  [[nodiscard]] constexpr double& operator[](int i) noexcept { return m_c[i]; }

  [[nodiscard]] constexpr double operator[](int i) const noexcept {
    return m_c[i];
  }

  constexpr vec3& operator+=(const vec3& other) noexcept {
    m_c[0] += other.x();
    m_c[1] += other.y();
    m_c[2] += other.z();
    return *this;
  }

  [[nodiscard]] constexpr vec3 operator+(const vec3& other) const noexcept {
    return vec3(x() + other.x(), y() + other.y(), z() + other.z());
  }

  constexpr vec3& operator-=(const vec3& other) noexcept {
    return *this += -other;
  }

  [[nodiscard]] constexpr vec3 operator-() const noexcept {
    return vec3(-m_c[0], -m_c[1], -m_c[2]);
  }

  [[nodiscard]] constexpr vec3 operator-(const vec3& other) const noexcept {
    return *this + (-other);
  }

  constexpr vec3& operator*=(double t) noexcept {
    m_c[0] *= t;
    m_c[1] *= t;
    m_c[2] *= t;
    return *this;
  }

  constexpr vec3 operator*(double t) const noexcept {
    return vec3(x() * t, y() * t, z() * t);
  }

  constexpr vec3 operator*(const vec3& v) const noexcept {
    return vec3(x() * v.x(), y() * v.y(), z() * v.z());
  }

  constexpr vec3& operator/=(double t) { return *this *= 1 / t; }

  constexpr vec3 operator/(double t) const { return *this * (1 / t); }

  [[nodiscard]] constexpr double norm() const noexcept {
    return std::sqrt(norm_squared());
  }
  [[nodiscard]] constexpr double norm_squared() const noexcept {
    return x() * x() + y() * y() + z() * z();
  }

  [[nodiscard]] constexpr vec3 unit_vector() const { return *this / norm(); }

  [[nodiscard]] bool near_zero() const noexcept {
    return std::fabs(x()) < eps && std::fabs(y()) < eps && std::fabs(z()) < eps;
  }
};

constexpr vec3 operator*(double t, const vec3& v) noexcept { return v * t; }

[[nodiscard]] constexpr double dot(const vec3& u, const vec3& v) noexcept {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

[[nodiscard]] constexpr vec3 cross(const vec3& u, const vec3& v) noexcept {
  return vec3(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x());
}

[[nodiscard]] inline vec3 random_on_emisphere(const vec3& normal) {
  auto unit = vec3::random_unit_vector();
  return dot(unit, normal) > 0.0 ? unit : unit;
}

[[nodiscard]] inline vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2 * dot(v, n) * n;
}

[[nodiscard]] inline vec3 refract(const vec3& uv, const vec3& n,
                                  double etai_over_etat) noexcept {
  auto cos_theta = std::fmin(dot(-uv, n), 1.0);
  auto r_out_perp = etai_over_etat * (uv + cos_theta * n);
  auto r_out_parallel =
      -std::sqrt(std::fabs(1.0 - r_out_perp.norm_squared())) * n;
  return r_out_perp + r_out_parallel;
}

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

using point = vec3;

#endif
