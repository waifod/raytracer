#include "hittable.hpp"
#include "hittable_list.hpp"
#include "ray.hpp"

bool hittable_list::hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const {
  hit_record temp_rec;
  auto hit_anything {false};
  auto closest_so_far {ray_tmax};

  std::for_each(begin(objects), end(objects), [&](const auto& obj) {
                if (obj->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                  hit_anything = true;
                  closest_so_far = temp_rec.t;
                  rec = temp_rec;
                }
  });

  return hit_anything;
}
