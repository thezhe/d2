#include "thezhe/d2/D2.hpp"
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index,
// cppcoreguidelines-pro-bounds-pointer-arithmetic)
namespace thezhe::d2
{
D2::D2() noexcept = default;
D2::D2(value_t t) noexcept
{
    *this = indexedOp([t]([[maybe_unused]] std::size_t i) { return t; });
}
D2::D2(std::initializer_list<value_t> data) noexcept
{
    *this = indexedOp([data]([[maybe_unused]] std::size_t i)
                      { return std::begin(data)[i]; });
}
D2 D2::operator+=(D2 b) noexcept
{
    *this = indexedOp([this, b](size_t i) { return data[i] + b.data[i]; });
    return *this;
}
D2 D2::operator-=(D2 b) noexcept
{
    *this = indexedOp([this, b](size_t i) { return data[i] - b.data[i]; });
    return *this;
}
D2 D2::operator*=(D2 b) noexcept
{
    *this = indexedOp([this, b](size_t i) { return data[i] * b.data[i]; });
    return *this;
}
D2 D2::operator/=(D2 b) noexcept
{
    *this = indexedOp([this, b](size_t i) { return data[i] / b.data[i]; });
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
D2 D2::sqrt() const
{
    return indexedOp([this](std::size_t i) { return std::sqrt(data[i]); });
}
D2 D2::abs() const
{
    return indexedOp([this](std::size_t i) { return std::abs(data[i]); });
}
D2 D2::tan() const
{
    return indexedOp([this](std::size_t i) { return std::tan(data[i]); });
}
D2 D2::min(D2 b) const noexcept
{
    return indexedOp([this, b](std::size_t i)
                     { return std::min(data[i], b.data[i]); });
}
D2 D2::max(D2 b) const noexcept
{
    return indexedOp([this, b](std::size_t i)
                     { return std::max(data[i], b.data[i]); });
}
D2 D2::pow(D2 b) const
{
    return indexedOp([this, b](std::size_t i)
                     { return std::pow(data[i], b.data[i]); });
}
D2 D2::lerp(D2 b, D2 c) const noexcept
{
    return indexedOp([this, b, c](std::size_t i)
                     { return std::lerp(data[i], b.data[i], c.data[i]); });
}
D2 D2::iflt(D2 b, D2 c, D2 d) const noexcept
{
    return indexedOp([this, b, c, d](std::size_t i)
                     { return c.data[i] < d.data[i] ? data[i] : b.data[i]; });
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
} // namespace thezhe::d2
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index,
// cppcoreguidelines-pro-bounds-pointer-arithmetic)
