# Dependencies
include(FetchContent)
FetchContent_Declare(
    osv_scanner_lock
    GIT_REPOSITORY https://github.com/thezhe/osv_scanner_lock.git
    GIT_TAG 1fc16ed031d6a407657baa2f5818393b27f2644b
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(osv_scanner_lock)
thezhe_osv_scanner_lock()
# Project
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
# cmake-lint: disable=C0103
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project("thezhe/D2")
# Build
add_library(D2 STATIC)
target_include_directories(D2 PUBLIC include)
target_sources(D2 PRIVATE src/D2.cpp)
add_library(thezhe::D2 ALIAS D2)
# Test
if(NOT PROJECT_IS_TOP_LEVEL)
    return()
endif()
enable_testing()
add_executable(test-D2)
target_sources(test-D2 PRIVATE test/D2.cpp)
target_link_libraries(test-D2 PRIVATE thezhe::D2)
add_test(NAME test-D2 COMMAND test-D2)
# ci
thezhe_add_ci()
