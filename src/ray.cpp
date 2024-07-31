#include "ray.hpp"

ray::ray(const point& origin, const vec3& direction) noexcept
    : m_origin{origin}, m_direction{direction} {}

const point& ray::origin() const noexcept { return m_origin; }
const vec3& ray::direction() const noexcept { return m_direction; }

point ray::at(double t) const noexcept { return m_origin + t * m_direction; }
