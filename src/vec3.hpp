#ifndef VEC3_H
#define VEC3_H

#include <array>

class vec3 {
  public:
    explicit vec3() noexcept = default;
    explicit vec3(double x, double y, double z) noexcept;

    double x() const noexcept;
    double y() const noexcept;
    double z() const noexcept;

    vec3& operator+=(const vec3& other) noexcept;
    vec3& operator-=(const vec3& other) noexcept;
    vec3& operator*=(double t) noexcept;
    vec3& operator/=(double t);
  
    double& operator[](int i) noexcept;
    double operator[](int i) const noexcept;

  private:
    std::array<double, 3> m_c{0,0,0};
};

vec3 operator+(const vec3& u, const vec3& v) noexcept;

vec3 operator-(const vec3& u) noexcept;
vec3 operator-(const vec3& u, const vec3& v) noexcept;

vec3 operator*(const vec3& u, double t) noexcept;
vec3 operator*(double t, const vec3& u) noexcept;
vec3 operator*(const vec3& u, const vec3& v) noexcept;

vec3 operator/(const vec3& u, double t);
    
double dot(const vec3& u, const vec3& v) noexcept;
vec3 cross(const vec3& u, const vec3& v) noexcept;
    
double norm(const vec3& u) noexcept;
double norm_squared(const vec3& u) noexcept;

vec3 unit_vector(const vec3& u);

std::ostream& operator<<(std::ostream& out, const vec3& u);

using point = vec3;

#endif
