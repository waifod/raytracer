#include "hittable_list.hpp"

#include "hittable.hpp"
#include "interval.hpp"
#include "ray.hpp"

bool hittable_list::hit(const ray& r, interval ray_t, hit_record& rec) const {
  hit_record temp_rec;
  auto hit_anything{false};
  auto closest_so_far{ray_t.end};

  std::for_each(begin(objects), end(objects), [&](const auto& obj) {
    if (obj->hit(r, interval(ray_t.start, closest_so_far), temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  });

  return hit_anything;
}
