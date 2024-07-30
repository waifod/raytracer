#include <cmath>
#include <iostream>

#include "vec3.hpp"

constexpr vec3::vec3(double x, double y, double z) noexcept : m_c{x,y,z} {}

constexpr double vec3::x() const noexcept { return m_c[0]; }
constexpr double vec3::y() const noexcept { return m_c[1]; }
constexpr double vec3::z() const noexcept { return m_c[2]; }

constexpr vec3& vec3::operator+=(const vec3& other) noexcept {
  m_c[0] += other.x();
  m_c[1] += other.y();
  m_c[2] += other.z();
  return *this;
}

constexpr vec3& vec3::operator-=(const vec3& other) noexcept {
  return *this += -other;
}

constexpr vec3& vec3::operator*=(double t) noexcept {
  m_c[0] *= t;
  m_c[1] *= t;
  m_c[2] *= t;
  return *this;
}

constexpr vec3& vec3::operator/=(double t) {
  return *this *= (1/t);
}

constexpr double vec3::operator[](int i) const noexcept {
  return m_c[i];
}

constexpr double& vec3::operator[](int i) noexcept {
  return m_c[i];
}

constexpr vec3 operator+(const vec3& u, const vec3& v) noexcept {
  return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

constexpr vec3 operator-(const vec3& u) noexcept {
  return vec3(-u.x(), -u.y(), -u.z());
}

constexpr vec3 operator-(const vec3& u, const vec3& v) noexcept {
  return u + (-v);
}

constexpr vec3 operator*(const vec3& v, double t) noexcept {
  return vec3(v.x()*t, v.y()*t, v.z()*t);
}

constexpr vec3 operator*(double t, const vec3& v) noexcept { return v*t; }

constexpr vec3 operator*(const vec3& u, const vec3& v) noexcept {
  return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

constexpr vec3 operator/(const vec3& u, double t) {
  return u * (1/t);
}

constexpr double dot(const vec3& u, const vec3& v) noexcept {
  return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}

constexpr vec3 cross(const vec3& u, const vec3& v) noexcept {
  return vec3(u.y() * v.z() - u.z() * v.y(),
              u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x());
}

constexpr double norm(const vec3& u) noexcept {
  return std::sqrt(norm_squared(u));
}

constexpr double norm_squared(const vec3& u) noexcept { 
  return u.x()*u.x() + u.y()*u.y() + u.z()*u.z(); 
}

constexpr vec3 unit_vector(const vec3& u) { return u/norm(u); }

std::ostream& operator<<(std::ostream& out, const vec3& u) {
    return out << u.x() << ' ' << u.y() << ' ' << u.z();
}
