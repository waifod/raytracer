#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
  public:
    explicit ray() noexcept = default;
    explicit ray(const point& origin, const vec3& direction) noexcept;

    const point& origin() const noexcept;
    const vec3& direction() const noexcept;

    point at(double t) const noexcept;

  private:
    point m_origin;
    vec3 m_direction;
};

#endif
