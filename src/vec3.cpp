#include <cmath>

#include "vec3.hpp"

vec3::vec3(double x, double y, double z) noexcept : m_c{x,y,z} {}

double vec3::x() const noexcept { return m_c[0]; }
double vec3::y() const noexcept { return m_c[1]; }
double vec3::z() const noexcept { return m_c[2]; }

vec3& vec3::operator+=(const vec3& other) noexcept {
  m_c[0] += other.x();
  m_c[1] += other.y();
  m_c[2] += other.z();
  return *this;
}

vec3& vec3::operator-=(const vec3& other) noexcept {
  return *this += -other;
}

vec3& vec3::operator*=(double t) noexcept {
  m_c[0] *= t;
  m_c[1] *= t;
  m_c[2] *= t;
  return *this;
}

vec3& vec3::operator/=(double t) {
  return *this *= (1/t);
}

double vec3::operator[](int i) const noexcept {
  return m_c[i];
}

double& vec3::operator[](int i) noexcept {
  return m_c[i];
}

vec3 operator+(const vec3& u, const vec3& v) noexcept {
  return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

vec3 operator-(const vec3& u) noexcept {
  return vec3(-u.x(), -u.y(), -u.z());
}

vec3 operator-(const vec3& u, const vec3& v) noexcept {
  return u + (-v);
}

vec3 operator*(const vec3& v, double t) noexcept {
  return vec3(v.x()*t, v.y()*t, v.z()*t);
}

vec3 operator*(double t, const vec3& v) noexcept { return v*t; }

vec3 operator*(const vec3& u, const vec3& v) noexcept {
  return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

vec3 operator/(const vec3& u, double t) {
  return u * (1/t);
}

double dot(const vec3& u, const vec3& v) noexcept {
  return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}

vec3 cross(const vec3& u, const vec3& v) noexcept {
  return vec3(u.y() * v.z() - u.z() * v.y(),
              u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x());
}

double norm(const vec3& u) noexcept {
  return std::sqrt(norm_squared(u));
}

double norm_squared(const vec3& u) noexcept { 
  return u.x()*u.x() + u.y()*u.y() + u.z()*u.z(); 
}

vec3 unit_vector(const vec3& u) { return u/norm(u); }
