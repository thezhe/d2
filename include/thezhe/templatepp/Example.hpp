#pragma once
#include "detail/DetailExample.hpp"
namespace thezhe::templatepp
{
class Example
{
public:
    constexpr Example() noexcept = default;
    [[nodiscard]] constexpr auto get() const noexcept
    {
        return detailExample.value;
    }
private:
    detail::DetailExample detailExample{};
};
} // namespace thezhe::templatepp
