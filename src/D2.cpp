#include "thezhe/d2/D2.hpp"
#include <cmath>
#include <cstdint>
#include <type_traits>
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index,
// cppcoreguidelines-pro-bounds-pointer-arithmetic)
namespace thezhe::d2
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
D2 D2::operator+=(D2 b) noexcept
{
    *this = indexedOp([this, b](auto i) { return data[i] + b.data[i]; });
    return *this;
}
D2 D2::operator-=(D2 b) noexcept
{
    *this = indexedOp([this, b](auto i) { return data[i] - b.data[i]; });
    return *this;
}
D2 D2::operator*=(D2 b) noexcept
{
    *this = indexedOp([this, b](auto i) { return data[i] * b.data[i]; });
    return *this;
}
D2 D2::operator/=(D2 b) noexcept
{
    *this = indexedOp([this, b](auto i) { return data[i] / b.data[i]; });
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
D2 D2::utrunc() const noexcept
{
    return indexedOp([this](auto i)
                     { return static_cast<std::int_fast32_t>(data[i]); });
}
D2 D2::sqrt() const
{
    return indexedOp([this](auto i) { return std::sqrt(data[i]); });
}
D2 D2::abs() const
{
    return indexedOp([this](auto i) { return std::fabs(data[i]); });
}
D2 D2::tan() const
{
    return indexedOp([this](auto i) { return std::tan(data[i]); });
}
D2 D2::min(D2 b) const noexcept
{
    return indexedOp([this, b](auto i)
                     { return std::fmin(data[i], b.data[i]); });
}
D2 D2::max(D2 b) const noexcept
{
    return indexedOp([this, b](auto i)
                     { return std::fmax(data[i], b.data[i]); });
}
D2 D2::pow(D2 b) const
{
    return indexedOp([this, b](auto i)
                     { return std::pow(data[i], b.data[i]); });
}
D2 D2::lerp(D2 b, D2 c) const noexcept
{
    return indexedOp([this, b, c](auto i)
                     { return std::lerp(data[i], b.data[i], c.data[i]); });
}
D2 D2::iflt(D2 b, D2 c, D2 d) const noexcept
{
    return indexedOp([this, b, c, d](auto i)
                     { return data[i] < b.data[i] ? c.data[i] : d.data[i]; });
}
D2 operator+(D2 a, D2 b) noexcept
{
    a += b;
    return a;
}
D2 operator-(D2 a, D2 b) noexcept
{
    a -= b;
    return a;
}
D2 operator*(D2 a, D2 b) noexcept
{
    a *= b;
    return a;
}
D2 operator/(D2 a, D2 b) noexcept
{
    a /= b;
    return a;
}
bool operator==(D2 a, D2 b) noexcept
{
    return a.data == b.data;
}
// Preconditions
static_assert(sizeof(D2) == alignof(D2));
static_assert(sizeof(D2) == sizeof(double) * 2);
static_assert(std::is_trivially_copyable_v<D2>);
static_assert(std::is_standard_layout_v<D2>);
static_assert(std::is_nothrow_copy_constructible_v<D2>
              && std::is_nothrow_copy_assignable_v<D2>
              && std::is_nothrow_destructible_v<D2>);
} // namespace thezhe::d2
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index,
// cppcoreguidelines-pro-bounds-pointer-arithmetic)
