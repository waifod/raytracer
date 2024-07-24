#include <array>

class vec3 {
  public:
    explicit vec3() noexcept = default;
    explicit vec3(double x, double y, double z) noexcept;

    inline double x() const noexcept;
    inline double y() const noexcept;
    inline double z() const noexcept;

    inline vec3& operator+=(const vec3& other) noexcept;
    inline vec3& operator-=(const vec3& other) noexcept;
    inline vec3& operator*=(double t) noexcept;
    inline vec3& operator/=(double t);
  
    inline double& operator[](int i) noexcept;
    inline double operator[](int i) const noexcept;

  private:
    std::array<double, 3> m_c{0,0,0};
};

inline vec3 operator+(const vec3& u, const vec3& v) noexcept;

inline vec3 operator-(const vec3& u) noexcept;
inline vec3 operator-(const vec3& u, const vec3& v) noexcept;

inline vec3 operator*(const vec3& u, double t) noexcept;
inline vec3 operator*(double t, const vec3& u) noexcept;
inline vec3 operator*(const vec3& u, const vec3& v) noexcept;

inline vec3 operator/(const vec3& u, double t);
    
inline double dot(const vec3& u, const vec3& v) noexcept;
inline vec3 cross(const vec3& u, const vec3& v) noexcept;
    
inline double norm(const vec3& u) noexcept;
inline double norm_squared(const vec3& u) noexcept;

inline vec3 unit_vector(const vec3& u);

inline std::ostream& operator<<(std::ostream& out, const vec3& u);

using point = vec3;
