#include <cstdlib>
#include <thezhe/d2.hpp>
// TODO "CXXFLAGS": "-fopt-info-missed=missed.txt"
// TODO compiler explorer see disassembly
using D2 = thezhe::d2::D2;
void test_ctors() {}
void test_assignment() {}
void test_arithmetic() {}
void test_math() {}
int main()
{
    test_ctors();
    test_assignment();
    test_arithmetic();
    test_math();
    // Template specialization and object
    constexpr D2 d2{ 1.0, 1.0 };
    // Constructors
    constexpr D2 avec_copy_ctor{ d2 };
    static_assert(avec_copy_ctor == d2);
    // Assignment operators
    D2 avec_copy{};
    avec_copy = d2;
    static_assert(avec_copy_ctor == d2);
    avec_copy += 1;
    // Assignment operators
    // Arithmetic operators
    // static_assert(D2(2.0, 4.0) == avec_copy + avec_copy);
    // avec128d_copied = avec128d_copied * d2;
    // auto test = -avec128d_copied;
    // Intrinsic math functions
    return EXIT_SUCCESS;
}
