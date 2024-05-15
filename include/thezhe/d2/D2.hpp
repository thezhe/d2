#pragma once
#include <array>
#include <cstddef>
// NOLINTBEGIN(google-explicit-constructor,hicpp-explicit-conversions)
namespace thezhe::d2
{
/*!
 * @brief Auto-vectorization-friendly pass-by-value `double` pair
 */
class D2 final
{
public:
    using value_t = double;
    D2() noexcept;
    D2(value_t lr) noexcept;
    D2(value_t l, value_t r) noexcept;
    D2 operator+=(D2 b) noexcept;
    D2 operator-=(D2 b) noexcept;
    D2 operator*=(D2 b) noexcept;
    D2 operator/=(D2 b) noexcept;
    friend bool operator==(D2 a, D2 b) noexcept;
    /*!
     * @brief Squared
     */
    [[nodiscard]] D2 sq() const noexcept;
    /*!
     * @brief Cubed
     */
    [[nodiscard]] D2 cb() const noexcept;
    // TODO reductions
    // TODO might not need trunc (do with scalars)
    /*!
     * @brief Truncate by casting to `std::size_t`
     * @pre Values are between `std::numeric_limits<std::size_t>::min()` and
     * `std::numeric_limits<std::size_t>::max()`
     */
    [[nodiscard]] D2 utrunc() const noexcept;
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
    static constexpr std::size_t size_v = 2UL;
    template<typename IndexedOp>
        requires std::is_invocable_r_v<value_t, IndexedOp, std::size_t>
    static D2 indexedOp(IndexedOp op)
    {
        D2 retval{};
        for (std::size_t i = 0; i < size_v; ++i)
        {
            retval.data[i] = op(i); // NOLINT
        }
        return retval;
    }
    alignas(sizeof(value_t) * size_v) std::array<value_t, size_v> data{};
};
[[nodiscard]] D2 operator+(D2 a, D2 b) noexcept;
[[nodiscard]] D2 operator-(D2 a, D2 b) noexcept;
[[nodiscard]] D2 operator*(D2 a, D2 b) noexcept;
[[nodiscard]] D2 operator/(D2 a, D2 b) noexcept;
[[nodiscard]] bool operator==(D2 a, D2 b) noexcept;
} // namespace thezhe::d2
// NOLINTEND(google-explicit-constructor,hicpp-explicit-conversions)
