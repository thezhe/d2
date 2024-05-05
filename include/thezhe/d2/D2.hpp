// cppcheck-suppress-file[passedByValue,unusedFunction]
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index,
// google-explicit-constructor)
#pragma once
#include "detail/D2.hpp"
#include <cmath>
#include <type_traits>
namespace thezhe::d2
{
/*!
 * @brief Auto-vectorization-friendly `double` pair
 * @pre See `thezhe::d2::pre`
 * @attention Pass by value
 */
class D2 final : public detail::D2
{
    // Ctors
    D2() noexcept;
    D2(value_t t) noexcept;
    D2(std::initializer_list<value_t> data) noexcept;
    // Assignment
    D2 operator+=(D2 other) noexcept;
    D2 operator-=(D2 other) noexcept;
    D2 operator*=(D2 other) noexcept;
    D2 operator/=(D2 other) noexcept;
    /*!
     * @brief Default comparison operator. Does NOT account for floating-point
     * error.
     */
    friend bool operator==(D2 a, D2 b) noexcept = default;
    /*!
     * @brief TODO (vec versions)
     * lerp
     * fmod/ceil/floor/remainder
     */
    [[nodiscard]] D2 min(D2 other) const;
    [[nodiscard]] D2 max(D2 other) const;
    [[nodiscard]] D2 pow(D2 other) const;
    [[nodiscard]] D2 sqrt() const;
    [[nodiscard]] D2 abs() const;
    [[nodiscard]] D2 tan() const;
    [[nodiscard]] D2 lerp(D2 b, D2 c) const noexcept;
    /*!
     * @brief Pseudo code `a[i] < b[i] ? *this[i] : other[i]`
     */
    [[nodiscard]] D2 iflt(D2 other, D2 a, D2 b) const noexcept;
    /*!
     * @brief Squared
     */
    [[nodiscard]] D2 sq() const noexcept;
    /*!
     * @brief Cubed
     */
    [[nodiscard]] D2 cb() const noexcept;
};
[[nodiscard]] D2 operator+(D2 a, D2 b) noexcept;
[[nodiscard]] D2 operator-(D2 a, D2 b) noexcept;
[[nodiscard]] D2 operator*(D2 a, D2 b) noexcept;
[[nodiscard]] D2 operator/(D2 a, D2 b) noexcept;
} // namespace thezhe::d2
namespace thezhe::d2::pre
{
template<typename T>
constexpr bool is_entirely_aligned_v{ sizeof(T) == alignof(T) };
template<typename T>
constexpr bool is_128_bit_v{ sizeof(T) % 16 == 0 };
template<typename T>
constexpr bool is_nothrow_implicit_v{ std::is_nothrow_default_constructible_v<T>
                                      && std::is_nothrow_copy_constructible_v<T>
                                      && std::is_nothrow_move_constructible_v<T>
                                      && std::is_nothrow_copy_assignable_v<T>
                                      && std::is_nothrow_move_assignable_v<T>
                                      && std::is_nothrow_destructible_v<T>
                                      && !std::has_virtual_destructor_v<T> };
/*!
 * @brief D2 type trait value
 */
template<typename T>
constexpr bool is_d2_v{ is_entirely_aligned_v<T> && is_128_bit_v<T>
                        && is_nothrow_implicit_v<T>
                        && std::is_trivially_copyable_v<T>
                        && std::is_standard_layout_v<T> };
static_assert(is_d2_v<::thezhe::d2::D2>);
} // namespace thezhe::d2::pre
// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index,
// google-explicit-constructor)
