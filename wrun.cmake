#[[
Run a url as a CMake script

    cmake -P <path-to-wrun.cmake> <url>

Fatal if: <url> content fails
Dependencies: curl
]]

# See `COMMAND_ERROR_IS_FATAL` in `execute_process`
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
# Dependencies
execute_process(COMMAND curl --version OUTPUT_QUIET COMMAND_ERROR_IS_FATAL ANY)
# CLI
math(EXPR argc_m_1 "${CMAKE_ARGC} - 1")
set(wrun_url "${CMAKE_ARGV${argc_m_1}}")
if(NOT wrun_url)
    message(FATAL_ERROR "Usage: cmake -P <path-to-wrun.cmake> <url>")
endif()
# Store <url> content in `curl_output`
execute_process(
    COMMAND curl -fsSL "${wrun_url}"
    OUTPUT_VARIABLE curl_output ECHO_ERROR_VARIABLE COMMAND_ERROR_IS_FATAL ANY)
# Run `curl_output`
cmake_language(EVAL CODE "${curl_output}")
