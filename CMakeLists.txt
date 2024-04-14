# Settings
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
# cmake-lint: disable=C0103
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
enable_testing()
# Project
project(d2)
# Build
add_library(d2 INTERFACE)
target_include_directories(d2 INTERFACE include)
add_library(thezhe::d2 ALIAS d2)
# Test
if(NOT PROJECT_IS_TOP_LEVEL)
    return()
endif()
add_executable(main-test main-test.cpp)
target_link_libraries(main-test thezhe::d2)
add_test(NAME main-test COMMAND main-test)
include(FetchContent)
