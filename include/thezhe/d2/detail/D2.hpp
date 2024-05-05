#pragma once
#include <array>
#include <type_traits>
namespace thezhe::d2::detail
{
class D2
{
public:
    using value_t = double;
    static constexpr std::size_t size_v = 2;
protected:
    template<typename D2Type, typename UnaryOp>
        requires std::is_invocable_r_v<value_t, UnaryOp, value_t>
    [[nodiscard]] D2Type unaryOp(D2Type a, UnaryOp op) const
    {
        return indexedOp([a, op](std::size_t i) { return op(a.data[i]); });
    }
    template<typename D2Type, typename BinaryOp>
        requires std::is_invocable_r_v<value_t, BinaryOp, value_t, value_t>
    D2Type binaryOp(D2Type b, BinaryOp op) const
    {
        return indexedOp([this, b, op](std::size_t i)
                         { return op(data[i], b.data[i]); });
    }
    template<typename D2Type, typename TernaryOp>
        requires std::
            is_invocable_r_v<value_t, TernaryOp, value_t, value_t, value_t>
        D2Type ternaryOp(D2Type b, D2Type c, TernaryOp op) const
    {
        return indexedOp([this, b, c, op](std::size_t i)
                         { return op(data[i], b.data[i], c.data[i]); });
    }
    template<typename D2Type, typename QuaternaryOp>
        requires std::is_invocable_r_v<value_t,
                                       QuaternaryOp,
                                       value_t,
                                       value_t,
                                       value_t,
                                       value_t>
    D2Type quaternaryOp(D2Type b, D2Type c, D2Type d, QuaternaryOp op) const
    {
        return indexedOp(
            [this, b, c, d, op](std::size_t i)
            { return op(data[i], b.data[i], c.data[i], d.data[i]); });
    }
private:
    template<typename IndexedOp, typename D2Type>
        requires std::is_invocable_r_v<value_t, IndexedOp, std::size_t>
                 && std::derived_from<D2Type, D2>
    static D2Type indexedOp(IndexedOp op)
    {
        D2Type retval{};
        for (std::size_t i = 0; i < size_v; ++i)
        {
            retval.data[i] = op(i);
        }
        return retval;
    }
    alignas(sizeof(value_t) * size_v) std::array<value_t, size_v> data{};
};
} // namespace thezhe::d2::detail
