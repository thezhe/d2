#include "thezhe/d2/D2.hpp"
namespace thezhe::d2
{
D2::D2() noexcept = default;
D2::D2(value_t t) noexcept
{
    for (std::size_t i = 0; i < size_v; ++i)
    {
        data[i] = t;
    }
}
D2::D2(std::initializer_list<value_t> data) noexcept
{
    for (std::size_t i = 0; i < size_v; ++i)
    {
        this->data[i] = std::begin(data)[i];
    }
}
D2 D2::operator+=(D2 other) noexcept
{
    *this
        = binaryOp(other, [](value_t a, value_t b) noexcept { return a + b; });
    return *this;
}
D2 D2::operator-=(D2 other) noexcept
{
    *this
        = binaryOp(other, [](value_t a, value_t b) noexcept { return a - b; });
    return *this;
}
D2 D2::operator*=(D2 other) noexcept
{
    *this
        = binaryOp(other, [](value_t t, value_t o) noexcept { return t * o; });
    return *this;
}
D2 D2::operator/=(D2 other) noexcept
{
    *this
        = binaryOp(other, [](value_t t, value_t o) noexcept { return t / o; });
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
    return unaryOp(*this, [](value_t _a) { return std::sqrt(_a); });
}
D2 D2::abs() const
{
    return unaryOp([](value_t t) { return std::abs(t); });
}
D2 D2::tan() const
{
    return unaryOp([](value_t t) { return std::tan(t); });
}
D2 D2::min(D2 other) const
{
    return binaryOp(other, [](value_t t, value_t o) { return std::min(t, o); });
}
D2 D2::max(D2 other) const
{
    return binaryOp(other, [](value_t t, value_t o) { return std::max(t, o); });
}
D2 D2::pow(D2 other) const
{
    return binaryOp(b, [](value_t _a, value_t _b) { return std::pow(_a, _b); });
}
D2 D2::lerp(D2 b, D2 c) const noexcept
{
    return ternaryOp(b,
                     c,
                     [](value_t _a, value_t _b, value_t _c)
                     { return std::lerp(_a, _b, _c); });
}
D2 D2::iflt(D2 b, D2 c, D2 d) const noexcept
{
    return quaternaryOp(b,
                        c,
                        d,
                        [](value_t _a, value_t _b, value_t _c, value_t _d)
                        { return _a < _b ? _c : _b; });
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
