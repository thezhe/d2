// cppcheck-suppress-file passedByValue
#pragma once
#include <array>
#include <cmath>
#define D2_STD_UNARY(__op)                                                     \
    [[nodiscard]] constexpr D2 __op()                                          \
        const noexcept(noexcept(std::__op(value_t())))                         \
    {                                                                          \
        D2 retval{};                                                           \
        for (std::size_t i = 0; i < size_v; ++i)                               \
        {                                                                      \
            retval.data[i] = std::__op(data[i]);                               \
        }                                                                      \
        return retval;                                                         \
    }
#define D2_STD_BINARY(__op)                                                    \
    [[nodiscard]] constexpr D2 __op(D2 b)                                      \
        const noexcept(noexcept(std::__op(value_t(), value_t())))              \
    {                                                                          \
        D2 retval{};                                                           \
        for (std::size_t i = 0; i < size_v; ++i)                               \
        {                                                                      \
            retval.data[i] = std::__op(data[i], b.data[i]);                    \
        }                                                                      \
        return retval;                                                         \
    }
#define D2_STD_TERNARY(__op)                                                   \
    [[nodiscard]] constexpr D2 __op(D2 b, D2 c)                                \
        const noexcept(noexcept(std::__op(value_t(), value_t(), value_t())))   \
    {                                                                          \
        D2 retval{};                                                           \
        for (std::size_t i = 0; i < size_v; ++i)                               \
        {                                                                      \
            retval.data[i] = std::__op(data[i], b.data[i], c.data[i]);         \
        }                                                                      \
        return retval;                                                         \
    }
#define D2_ARITHMETIC(__op)                                                    \
    constexpr D2 operator __op##=(D2 other) noexcept                           \
    {                                                                          \
        *this = transform(other,                                               \
                          [](value_t a, value_t b) noexcept                    \
                          { return a __op b; });                               \
        return *this;                                                          \
    }                                                                          \
    [[nodiscard]] friend constexpr D2 operator __op(D2 a, D2 b) noexcept       \
    {                                                                          \
        a __op## = b;                                                          \
        return a;                                                              \
    }
namespace thezhe::d2
{
/*!
 * @brief Auto-vectorization-friendly `std::array` facade
 * @pre See `thezhe::d2::preconditions`
 * @attention Pass by value
 */
class D2 final
{
public:
    using value_t = double;
    static constexpr std::size_t size_v = 2;
    constexpr D2(value_t t) noexcept // NOLINT
    {
        *this = transform([t]() noexcept { return t; });
    }
    template<typename... Ts>
    constexpr explicit D2(Ts... ts) noexcept : data({ ts... })
    {
    }
    D2_ARITHMETIC(+)
    D2_ARITHMETIC(-)
    D2_ARITHMETIC(*)
    D2_ARITHMETIC(/)
    friend constexpr D2 operator-(D2 a) noexcept
    {
        a *= -1;
        return a;
    }
    /*!
     * @brief Default comparison operator. Does NOT account for floating-point
     * error.
     */
    friend constexpr bool operator==(D2 a, D2 b) noexcept = default;
    /*!
     * @brief TODO (vec versions)
     * tanh
     * atan(2?)
     * sqrt (single simd instruction)
     * binary min/max
     * pow
     * exp
     * lerp
     * fmod/ceil/floor/remainder
     */
    D2_STD_UNARY(sqrt)
    D2_STD_UNARY(abs)
    D2_STD_BINARY(min)
    D2_STD_BINARY(max)
    D2_STD_UNARY(tanh)
    D2_STD_BINARY(pow)
    D2_STD_UNARY(tan)
    /*!
     * @brief `a[i] < b[i] ? *this[i] : other[i]`
     */
    [[nodiscard]] constexpr D2 iflt(D2 other, D2 a, D2 b) const noexcept
    {
        return transform([a, b, other](std::size_t i, value_t t) noexcept
                         { return a.data[i] < b.data[i] ? t : other.data[i]; });
    }
    /*!
     * @brief Get squared
     */
    [[nodiscard]] constexpr D2 sq() const noexcept
    {
        D2 a{ *this };
        return a * a;
    }
    /*!
     * @brief Get cubed
     */
    [[nodiscard]] constexpr D2 cb() const noexcept
    {
        D2 a{ *this };
        return a * a * a;
    }
private:
    /*!
     * @brief Nullary transform
     */
    template<typename NullaryOp>
        requires std::is_invocable_r_v<value_t, NullaryOp>
    constexpr D2 transform(NullaryOp nullaryOp) const noexcept
    {
        return transform([nullaryOp]([[maybe_unused]] auto i,
                                     [[maybe_unused]] auto t) noexcept
                         { return nullaryOp(); });
    }
    /*!
     * @brief Unary transform
     */
    template<typename UnaryOp>
        requires std::is_invocable_r_v<value_t, UnaryOp, value_t>
    constexpr D2 transform(UnaryOp unaryOp) const noexcept
    {
        return transform([unaryOp]([[maybe_unused]] auto i, auto t) noexcept
                         { return unaryOp(t); });
    }
    /*!
     * @brief Binary transform
     */
    template<typename BinaryOp>
        requires std::
            is_nothrow_invocable_r_v<value_t, BinaryOp, value_t, value_t>
        constexpr D2 transform(D2 other, BinaryOp binaryOp) const noexcept
    {
        return transform([binaryOp, other](auto i, auto t) noexcept
                         { return binaryOp(t, other.data[i]); });
    }
    /*!
     * @brief Indexed unary transform
     *
     * @tparam EnumeratedTransform
     * @param enumeratedTransform
     */
    template<typename EnumeratedTransform>
        requires std::is_nothrow_invocable_r_v<value_t,
                                               EnumeratedTransform,
                                               std::size_t,
                                               value_t>
    constexpr D2
    transform(EnumeratedTransform enumeratedTransform) const noexcept
    {
        D2 retval{};
        for (std::size_t i = 0; i < size_v; ++i)
        {
            retval.data[i] = enumeratedTransform(i, data[i]);
        }
        return retval;
    }
    /*!
     * @brief `std::array` instance
     */
    alignas(sizeof(value_t) * size_v) std::array<value_t, size_v> data{};
};
} // namespace thezhe::d2
namespace thezhe::d2::preconditions
{
template<typename T>
constexpr bool is_entirely_aligned_v{ sizeof(T) == alignof(T) };
template<typename T>
constexpr bool is_128_bit_multiple_v{ sizeof(T) % 16 == 0 };
template<typename T>
constexpr bool is_nothrow_implicit_v{ std::is_nothrow_default_constructible_v<T>
                                      && std::is_nothrow_copy_constructible_v<T>
                                      && std::is_nothrow_move_constructible_v<T>
                                      && std::is_nothrow_copy_assignable_v<T>
                                      && std::is_nothrow_move_assignable_v<T>
                                      && std::is_nothrow_destructible_v<T>
                                      && !std::has_virtual_destructor_v<T> };
/*!
 * @brief Validates an `D2` specialization
 * @note `alignof(T) == alignof(typename T::data)`
 * @tparam T An `D2` specialization
 */
template<typename T>
constexpr bool is_valid_avec_v{ is_entirely_aligned_v<T>
                                && is_128_bit_multiple_v<T>
                                && is_nothrow_implicit_v<T> };
template<typename T>
constexpr bool is_valid_d2_v{ is_valid_avec_v<T> && sizeof(T) == 16 };
/*!
 * @brief 128-bit simd must be valid
 */
static_assert(is_valid_d2_v<::thezhe::d2::D2>);
} // namespace thezhe::d2::preconditions
