# Dependencies
include(FetchContent)
FetchContent_Declare(
    content_lock
    GIT_REPOSITORY https://github.com/thezhe/content_lock.git
    GIT_TAG 5ad74bf7e5360626d100e06eccfbcbbb06ab550d
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(content_lock)
thezhe_content_lock()
# Project
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
# cmake-lint: disable=C0103
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project("thezhe/d2")
# Build
add_library(d2 STATIC)
target_include_directories(d2 PUBLIC include)
target_sources(d2 PRIVATE src/D2.cpp)
add_library(thezhe::d2 ALIAS d2)
# Test
if(NOT PROJECT_IS_TOP_LEVEL)
    return()
endif()
enable_testing()
add_executable(test-D2)
target_sources(test-D2 PRIVATE test/D2.cpp)
target_link_libraries(test-D2 thezhe::d2)
add_test(NAME test-D2 COMMAND test-D2)
# ci
thezhe_add_ci()
