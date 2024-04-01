#include <cstdlib>
#include <ranges> // IWYU pragma: keep
#include <thezhe/avec.hpp>
// TODO "CXXFLAGS": "-fopt-info-missed=missed.txt"
// TODO compiler explorer see dissassembly
// TODO rename to D128
using Avec = thezhe::avec::Avec<>; // NOLINT
void test_ctors() {}
void test_assignment() {}
void test_arithmetic() {}
void test_math() {}
int main()
{
    // Template specialization and object
    constexpr Avec avec{ 1.0, 1.0 };
    // Constructors
    constexpr Avec avec_copy_ctor{ avec };
    static_assert(avec_copy_ctor == avec);
    // Assignment operators
    Avec avec_copy{};
    avec_copy = avec;
    static_assert(avec_copy_ctor == avec);
    avec_copy += 1;
    // Assignment operators
    // Arithmetic operators
    // static_assert(Avec(2.0, 4.0) == avec_copy + avec_copy);
    // avec128d_copied = avec128d_copied * avec;
    // auto test = -avec128d_copied;
    // Intrinsic math functions
    return EXIT_SUCCESS;
}
