#pragma once
#include <array>
#include <cstddef>
namespace thezhe
{
/*!
 * @brief Auto-vectorization-friendly pass-by-value `double` pair
 */
class D2 final
{
public:
    using data_type = std::array<double, 2>;
    using iterator = data_type::iterator;
    explicit D2() noexcept;
    explicit(false) D2(double lr) noexcept;
    explicit(false) D2(double l, double r) noexcept;
    [[nodiscard]] iterator begin();
    [[nodiscard]] iterator end();
    D2 operator+=(D2 b) noexcept;
    D2 operator-=(D2 b) noexcept;
    D2 operator*=(D2 b) noexcept;
    D2 operator/=(D2 b) noexcept;
    friend D2 operator+(D2 a, D2 b) noexcept
    {
        a += b;
        return a;
    }
    friend D2 operator-(D2 a, D2 b) noexcept
    {
        a -= b;
        return a;
    }
    friend D2 operator*(D2 a, D2 b) noexcept
    {
        a *= b;
        return a;
    }
    friend D2 operator/(D2 a, D2 b) noexcept
    {
        a /= b;
        return a;
    }
    [[nodiscard]] D2 sq() const noexcept;
    [[nodiscard]] D2 cb() const noexcept;
    // // TODO reductions
    // TODO negation, unary ops
    /*!
     * @brief Equivalent to pseudo-code `a[i] * b[i] + c[i]`
     */
    [[nodiscard]] D2 fma(D2 b, D2 c) const;
    [[nodiscard]] D2 sqrt() const;
    [[nodiscard]] D2 abs() const;
    [[nodiscard]] D2 tan() const;
    [[nodiscard]] D2 min(D2 b) const noexcept;
    [[nodiscard]] D2 max(D2 b) const noexcept;
    [[nodiscard]] D2 pow(D2 b) const;
    [[nodiscard]] D2 lerp(D2 b, D2 c) const noexcept;
    /*!
     * @brief Equivalent to pseudo-code `a[i] < b[i] ? c[i] : d[i]`
     */
    [[nodiscard]] D2 iflt(D2 b, D2 c, D2 d) const noexcept;
private:
    template<typename F>
        requires std::is_invocable_r_v<D2, F, std::size_t, double>
    [[nodiscard]] D2 transform(F f) const
    {
        D2 retval;
        for (std::size_t i = 0; i < data.size(); ++i)
        {
            retval.data[i] = f(i, data[i]);
        }
        return retval;
    }
    alignas(sizeof(data_type)) data_type data{};
};
} // namespace thezhe
