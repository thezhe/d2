# Settings
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
# cmake-lint: disable=C0103
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
enable_testing()
# Project
project(avec)
# Build
add_library(avec INTERFACE)
target_include_directories(avec INTERFACE include)
add_library(thezhe::avec ALIAS avec)
# Test
add_executable(main-test main-test.cpp)
target_link_libraries(main-test thezhe::avec)
add_test(NAME main-test COMMAND main-test)
include(FetchContent)
