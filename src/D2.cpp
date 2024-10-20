#include "thezhe/D2.hpp"
#include <cmath>
#include <ranges>
#include <type_traits>
namespace thezhe
{
D2::D2() noexcept = default;
D2::D2(double lr) noexcept
{
    data[0] = lr;
    data[1] = lr;
}
D2::D2(double l, double r) noexcept
{
    data[0] = l;
    data[1] = r;
}
D2::iterator D2::begin()
{
    return data.begin();
}
D2::iterator D2::end()
{
    return data.end();
}
D2 D2::operator+=(D2 b) noexcept
{
    *this = transform([b](auto i, auto t) { return t + b.data[i]; });
    return *this;
}
D2 D2::operator-=(D2 b) noexcept
{
    *this = transform([b](auto i, auto t) { return t - b.data[i]; });
    return *this;
}
D2 D2::operator*=(D2 b) noexcept
{
    *this = transform([b](auto i, auto t) { return t * b.data[i]; });
    return *this;
}
D2 D2::operator/=(D2 b) noexcept
{
    *this = transform([b](auto i, auto t) { return t / b.data[i]; });
    return *this;
}
D2 D2::sq() const noexcept
{
    D2 a{ *this };
    return a * a;
}
D2 D2::cb() const noexcept
{
    D2 a{ *this };
    return a * a * a;
}
D2 D2::fma(D2 b, D2 c) const
{
    return transform([b, c](auto i, auto t)
                     { return std::fma(t, b.data[i], c.data[i]); });
}
D2 D2::sqrt() const
{
    return transform([]([[maybe_unused]] auto i, auto t)
                     { return std::sqrt(t); });
}
D2 D2::abs() const
{
    return transform([]([[maybe_unused]] auto i, auto t)
                     { return std::abs(t); });
}
D2 D2::tan() const
{
    return transform([]([[maybe_unused]] auto i, auto t)
                     { return std::tan(t); });
}
D2 D2::min(D2 b) const noexcept
{
    return transform([b](auto i, auto t) { return std::min(t, b.data[i]); });
}
D2 D2::max(D2 b) const noexcept
{
    return transform([b](auto i, auto t) { return std::max(t, b.data[i]); });
}
D2 D2::pow(D2 b) const
{
    return transform([b](auto i, auto t) { return std::pow(t, b.data[i]); });
}
D2 D2::lerp(D2 b, D2 c) const noexcept
{
    return transform([b, c](auto i, auto t)
                     { return std::lerp(t, b.data[i], c.data[i]); });
}
D2 D2::iflt(D2 b, D2 c, D2 d) const noexcept
{
    return transform([b, c, d](auto i, auto t)
                     { return t < b.data[i] ? c.data[i] : d.data[i]; });
}
// Preconditions
static_assert(sizeof(D2) == alignof(D2));
static_assert(sizeof(D2) == sizeof(double) * 2);
static_assert(std::is_trivially_copyable_v<D2>);
static_assert(std::is_standard_layout_v<D2>);
static_assert(std::is_nothrow_copy_constructible_v<D2>
              && std::is_nothrow_copy_assignable_v<D2>
              && std::is_nothrow_destructible_v<D2>);
static_assert(std::ranges::range<D2>);
} // namespace thezhe
