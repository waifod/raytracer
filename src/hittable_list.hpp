#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.hpp"

class hittable_list : public hittable {
 public:
  [[nodiscard]] explicit hittable_list() noexcept = default;
  [[nodiscard]] explicit hittable_list(std::shared_ptr<hittable> obj) noexcept {
    add(obj);
  };

  void clear() noexcept { objects.clear(); };
  void add(std::shared_ptr<hittable> obj) noexcept {
    objects.emplace_back(obj);
  };

  [[nodiscard]] bool hit(const ray& r, double ray_tmin, double ray_tmax,
                         hit_record& rec) const override;

 private:
  std::vector<std::shared_ptr<hittable>> objects;
};

#endif
