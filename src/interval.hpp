#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.hpp"

class interval {
    public:
        double start;
        double end;

        [[nodiscard]] constexpr explicit interval() noexcept
        : start(infty)
        , end(-infty) {};

        [[nodiscard]] constexpr explicit interval(double start, double end) noexcept
        : start{start}
        , end{end} {};

        [[nodiscard]] constexpr double size() const noexcept { return end-start; };

        [[nodiscard]] constexpr bool contains(double x) const noexcept { return start <= x && x <= end; };
        [[nodiscard]] constexpr bool surrounds(double x) const noexcept { return start < x && x < end; };

        [[nodiscard]] constexpr double clamp(double x) const noexcept {
            if (x < start) return start;
            if (x > end) return end;
            return x;
        }

        [[nodiscard]] static const interval& empty() noexcept { 
            static const auto empty = interval();
            return empty;
        } 

        [[nodiscard]] static const interval& universe() noexcept { 
            static const auto universe = interval(-infty, infty);
            return universe;
        } 
};

#endif