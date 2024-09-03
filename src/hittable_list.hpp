#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.hpp"
#include "interval.hpp"

class hittable_list : public hittable {
 public:
  [[nodiscard]] explicit hittable_list() noexcept = default;
  [[nodiscard]] explicit hittable_list(std::unique_ptr<hittable> obj) noexcept {
    add(std::move(obj));
  };

  void clear() noexcept { objects.clear(); };
  void add(std::unique_ptr<hittable> obj) noexcept {
    objects.emplace_back(std::move(obj));
  };

  [[nodiscard]] bool hit(const ray& r, interval ray_t,
                         hit_record& rec) const noexcept override;

 private:
  std::vector<std::unique_ptr<hittable>> objects;
};

#endif
