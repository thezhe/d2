#undef NDEBUG
#include "thezhe/d2/D2.hpp"
#include <cassert>
using namespace thezhe::d2; // NOLINT
void test_ctors()
{
    const D2 ctor_default{};
    const D2 ctor1{ 1.0 };
    const D2 ctor2{ 1.0, 1.0 };
    const auto ctor_copy{ ctor2 };
}
void test_assignment()
{
    // // Template specialization and object
    // constexpr D2 d2{ 1.0, 1.0 };
    // // Constructors
    // constexpr D2 avec_copy_ctor{ d2 };
    // static_assert(avec_copy_ctor == d2);
    // // Assignment operators
    // D2 avec_copy{};
    // avec_copy = d2;
    // static_assert(avec_copy_ctor == d2);
    // avec_copy += 1;
    // Assignment operators
    // Arithmetic operators
    // static_assert(D2(2.0, 4.0) == avec_copy + avec_copy);
    // avec128d_copied = avec128d_copied * d2;
    // auto test = -avec128d_copied;
    // Intrinsic math functions
}
void test_arithmetic() {}
void test_math() {}
int main()
{
    test_ctors();
    test_assignment();
    test_arithmetic();
    test_math();
}
