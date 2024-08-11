#ifndef INTERVAL_H
#define INTERVAL_H

#include <numeric>
#include <numbers>

class interval {
    public:
        double start;
        double end;

        [[nodiscard]] constexpr explicit interval() noexcept
        : start(std::numeric_limits<double>::infinity())
        , end(-std::numeric_limits<double>::infinity()) {};

        [[nodiscard]] constexpr explicit interval(double start, double end) noexcept
        : start{start}
        , end{end} {};

        [[nodiscard]] constexpr double size() const noexcept { return end-start; };

        [[nodiscard]] constexpr bool contains(double x) const noexcept { return start <= x && x <= end; };
        [[nodiscard]] constexpr bool surrounds(double x) const noexcept { return start < x && x < end; };

        [[nodiscard]] static const interval& empty() noexcept { 
            static const auto empty = interval();
            return empty;
        } 

        [[nodiscard]] static const interval& universe() noexcept { 
            static const auto universe = interval(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
            return universe;
        } 
};

#endif