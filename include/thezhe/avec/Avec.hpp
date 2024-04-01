// cppcheck-suppress-file passedByValue
#pragma once
#include <array>
#include <cmath>
#define AVEC_STD_UNARY_OP(__op)                                                \
    [[nodiscard]] constexpr Avec __op()                                        \
        const noexcept(noexcept(std::__op(T())))                               \
    {                                                                          \
        Avec retval{};                                                         \
        for (std::size_t i = 0; i < n; ++i)                                    \
        {                                                                      \
            retval.data[i] = std::__op(data[i]);                               \
        }                                                                      \
        return retval;                                                         \
    }
#define AVEC_STD_BINARY_OP(__op)                                               \
    [[nodiscard]] constexpr Avec __op(Avec b)                                  \
        const noexcept(noexcept(std::__op(T(), T())))                          \
    {                                                                          \
        Avec retval{};                                                         \
        for (std::size_t i = 0; i < n; ++i)                                    \
        {                                                                      \
            retval.data[i] = std::__op(data[i], b.data[i]);                    \
        }                                                                      \
        return retval;                                                         \
    }
#define AVEC_STD_TERNARY_OP(__op)                                              \
    [[nodiscard]] constexpr Avec __op(Avec b, Avec c)                          \
        const noexcept(noexcept(std::__op(T(), T(), T())))                     \
    {                                                                          \
        Avec retval{};                                                         \
        for (std::size_t i = 0; i < n; ++i)                                    \
        {                                                                      \
            retval.data[i] = std::__op(data[i], b.data[i], c.data[i]);         \
        }                                                                      \
        return retval;                                                         \
    }
#define AVEC_ARITHMETIC_OP(__op)                                               \
    constexpr Avec operator __op##=(Avec other) noexcept                       \
    {                                                                          \
        *this = transform(other, [](T a, T b) noexcept { return a __op b; });  \
        return *this;                                                          \
    }                                                                          \
    [[nodiscard]] friend constexpr Avec operator __op(Avec a, Avec b) noexcept \
    {                                                                          \
        a __op## = b;                                                          \
        return a;                                                              \
    }
namespace thezhe::avec
{
/*!
 * @brief Auto-vectorizable `std::array` facade
 * @tparam T Element type. Must be floating-point.
 * @tparam n Number of elements
 * @pre See `thezhe::avec::preconditions`
 * @note Use like a floating-point type
 * @details In other words: pass by value and avoid mixing specializations for
 * best performance
 */
template<typename T = double, std::size_t n = 2>
    requires std::is_floating_point_v<T>
class Avec final
{
public:
    constexpr Avec(T t) noexcept // NOLINT
    {
        *this = transform([t]() noexcept { return t; });
    }
    template<typename... Ts>
    constexpr explicit Avec(Ts... ts) noexcept : data({ ts... })
    {
    }
    AVEC_ARITHMETIC_OP(+)
    AVEC_ARITHMETIC_OP(-)
    AVEC_ARITHMETIC_OP(*)
    AVEC_ARITHMETIC_OP(/)
    friend constexpr Avec operator-(Avec a) noexcept
    {
        a *= -1;
        return a;
    }
    /*!
     * @brief Default comparison operator. Does NOT account for floating-point
     * error.
     */
    friend constexpr bool operator==(Avec a, Avec b) noexcept = default;
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
    AVEC_STD_UNARY_OP(sqrt)
    AVEC_STD_UNARY_OP(abs)
    AVEC_STD_BINARY_OP(min)
    AVEC_STD_BINARY_OP(max)
    AVEC_STD_BINARY_OP(tanh)
    AVEC_STD_BINARY_OP(pow)
    AVEC_STD_BINARY_OP(tan)
    /*!
     * @brief `a[i] < b[i] ? *this[i] : other[i]`
     */
    [[nodiscard]] constexpr Avec iflt(Avec other, Avec a, Avec b) const noexcept
    {
        return transform([a, b, other](T t, std::size_t i) noexcept
                         { return a[i] < b[i] ? t : other.data[i]; });
    }
    /*!
     * @brief Get squared
     */
    [[nodiscard]] constexpr Avec sq() const noexcept
    {
        Avec a{ *this };
        return a * a;
    }
    /*!
     * @brief Get cubed
     */
    [[nodiscard]] constexpr Avec cb() const noexcept
    {
        Avec a{ *this };
        return a * a * a;
    }
private:
    /*!
     * @brief Nullary transform
     */
    template<typename NullaryOp>
        requires std::is_invocable_r_v<T, NullaryOp>
    constexpr Avec transform(NullaryOp nullaryOp) const noexcept
    {
        return transform([nullaryOp]([[maybe_unused]] auto i,
                                     [[maybe_unused]] auto t) noexcept
                         { return nullaryOp(); });
    }
    /*!
     * @brief Unary transform
     */
    template<typename UnaryOp>
        requires std::is_invocable_r_v<T, UnaryOp, T>
    constexpr Avec transform(UnaryOp unaryOp) const noexcept
    {
        return transform([unaryOp]([[maybe_unused]] auto i, auto t) noexcept
                         { return unaryOp(t); });
    }
    /*!
     * @brief Binary transform
     */
    template<typename BinaryOp>
        requires std::is_nothrow_invocable_r_v<T, BinaryOp, T, T>
    constexpr Avec transform(Avec other, BinaryOp binaryOp) const noexcept
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
        requires std::
            is_nothrow_invocable_r_v<T, EnumeratedTransform, std::size_t, T>
        constexpr Avec
        transform(EnumeratedTransform enumeratedTransform) const noexcept
    {
        Avec retval{};
        for (std::size_t i = 0; i < n; ++i)
        {
            retval.data[i] = enumeratedTransform(i, data[i]);
        }
        return retval;
    }
    /*!
     * @brief `std::array` instance
     */
    alignas(sizeof(T) * n) std::array<T, n> data{};
};
} // namespace thezhe::avec
namespace thezhe::avec::preconditions
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
 * @brief Validates an `Avec` specialization
 * @note `alignof(T) == alignof(typename T::data)`
 * @tparam T An `Avec` specialization
 */
template<typename T>
constexpr bool is_valid_avec_v{ is_entirely_aligned_v<T>
                                && is_128_bit_multiple_v<T>
                                && is_nothrow_implicit_v<T> };
template<typename T>
constexpr bool is_valid_avec_128_v{ is_valid_avec_v<T> && sizeof(T) == 16 };
/*!
 * @brief 128-bit simd must be valid
 */
static_assert(is_valid_avec_128_v<Avec<double, 2>>);
static_assert(is_valid_avec_128_v<Avec<float, 4>>);
} // namespace thezhe::avec::preconditions
