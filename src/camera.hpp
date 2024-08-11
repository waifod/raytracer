#ifndef CAMERA_H
#define CAMERA_H

#include "color.hpp"
#include "hittable.hpp"
#include "vec3.hpp"
#include "hittable.hpp"
#include "ray.hpp"

class camera {
    public:
        double aspect_ratio {1.0};
        int image_width {100};

        [[nodiscard]] explicit camera() = default;
        void render(const hittable& world);

    private:
        // NOTE: we can keep image_height first because
        //  it does not impact the size of this class.
        int    image_height;   // Rendered image height
        point center;         // Camera center
        point pixel00_loc;    // Location of pixel 0, 0
        vec3   pixel_delta_u;  // Offset to pixel to the right
        vec3   pixel_delta_v;  // Offset to pixel below

        void initialize();
        color ray_color(const ray& r, const hittable& world) const;
};

#endif