#include <cassert>
#include <iostream>
#include <string>
#include <thezhe/templatepp.hpp>
auto main() -> int
{
    using Example = thezhe::templatepp::Example;
    // static_assert
    static constexpr Example example{};
    static_assert(example.get());
    // assert
    const std::string ci_build_version{ CI_BUILD_VERSION };
    assert(!ci_build_version.empty());
    // debug output
    std::cout << "CI_BUILD_VERSION=" << ci_build_version << '\n';
    return EXIT_SUCCESS;
}
