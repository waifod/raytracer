#include <cmath>
#include <iostream>

#include "src/color.hpp"
#include "src/ray.hpp"
#include "src/vec3.hpp"

// Image
constexpr double ASPECT_RATIO {16.0/9.0};
constexpr int IMAGE_HEIGHT {800};

constexpr int getImageWidth() {
    auto width {int(double(IMAGE_HEIGHT) * ASPECT_RATIO)};
    return width < 1 ? 1 : width;
}
constexpr int IMAGE_WIDTH {getImageWidth()};

// Camera
constexpr double FOCAL_LENGTH {1.0};
constexpr double VIEWPORT_HEIGHT {2.0};
constexpr double VIEWPORT_WIDTH {VIEWPORT_HEIGHT * (double(IMAGE_WIDTH) / IMAGE_HEIGHT)};
constexpr point CAMERA_CENTER {point(0,0,0)};

double hit_sphere(const point& center, double radius, const ray& r) {
    auto oc_dir {center - r.origin()};
    auto a {r.direction().norm()};
    auto h {dot(r.direction(), oc_dir)};
    auto c {oc_dir.norm() - radius*radius};
    auto discriminant {h*h - a*c};

    if (discriminant < 0) {
        return -1.0;
    }
    return (-h-std::sqrt(discriminant)) / a;
}

color ray_color(const ray& r) {
    auto t {hit_sphere(point(0,0,-1), 0.5, r)};
    if (t > 0.0) {
        auto N {(r.at(t)-vec3(0,0,-1)).unit_vector()};
        return color(N.x()+1, N.y()+1, N.z()+1) / 2;
    }
    auto unit_direction {r.direction().unit_vector()};
    auto a {(unit_direction.y()+1.0)/2};
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    static constexpr auto viewport_u {vec3(VIEWPORT_WIDTH, 0, 0)};
    static constexpr auto viewport_v {vec3(0, -VIEWPORT_HEIGHT, 0)};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    static constexpr auto pixel_delta_u {viewport_u / IMAGE_WIDTH};
    static constexpr auto pixel_delta_v {viewport_v / IMAGE_HEIGHT};

    // Calculate the location of the upper left pixel.
    static constexpr auto viewport_upper_left {CAMERA_CENTER - vec3(0,0,FOCAL_LENGTH) - viewport_u/2 - viewport_v/2};
    static constexpr auto pixel00_loc {viewport_upper_left + (pixel_delta_u + pixel_delta_v)/2};

    // Render

    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int j = 0; j < IMAGE_HEIGHT; j++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; i++) {
            auto pixel_center {pixel00_loc + i*pixel_delta_u + j*pixel_delta_v};
            auto ray_direction {pixel_center - CAMERA_CENTER};
            auto r {ray(CAMERA_CENTER, ray_direction)};
            auto pixel_color {ray_color(r)};

            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\nDone.\n";
}
