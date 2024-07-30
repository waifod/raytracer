#ifndef VEC3_H
#define VEC3_H

#include <array>

class vec3 {
  public:
    constexpr explicit vec3() noexcept = default;
    constexpr explicit vec3(double x, double y, double z) noexcept;

    constexpr double x() const noexcept;
    constexpr double y() const noexcept;
    constexpr double z() const noexcept;

    constexpr vec3& operator+=(const vec3& other) noexcept;
    constexpr vec3& operator-=(const vec3& other) noexcept;
    constexpr vec3& operator*=(double t) noexcept;
    constexpr vec3& operator/=(double t);
  
    constexpr double& operator[](int i) noexcept;
    constexpr double operator[](int i) const noexcept;

  private:
    std::array<double, 3> m_c{0,0,0};
};

constexpr vec3 operator+(const vec3& u, const vec3& v) noexcept;

constexpr vec3 operator-(const vec3& u) noexcept;
constexpr vec3 operator-(const vec3& u, const vec3& v) noexcept;

constexpr vec3 operator*(const vec3& u, double t) noexcept;
constexpr vec3 operator*(double t, const vec3& u) noexcept;
constexpr vec3 operator*(const vec3& u, const vec3& v) noexcept;

constexpr vec3 operator/(const vec3& u, double t);
    
constexpr double dot(const vec3& u, const vec3& v) noexcept;
constexpr vec3 cross(const vec3& u, const vec3& v) noexcept;
    
constexpr double norm(const vec3& u) noexcept;
constexpr double norm_squared(const vec3& u) noexcept;

constexpr vec3 unit_vector(const vec3& u);

std::ostream& operator<<(std::ostream& out, const vec3& u);

using point = vec3;

#endif
