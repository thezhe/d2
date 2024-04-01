# https://github.com/thezhe/wrun.cmake/tree/v0.1.0

# Settings
cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
# CLI
set(wrun_url "${CMAKE_ARGV3}")
# Validate
if(NOT wrun_url)
    message(FATAL_ERROR "ERROR: Invalid URL")
endif()
# Fetch
execute_process(
    COMMAND curl -fsSL "${wrun_url}"
    OUTPUT_VARIABLE curl_output ECHO_ERROR_VARIABLE COMMAND_ERROR_IS_FATAL ANY)
# Run
cmake_language(EVAL CODE "${curl_output}")
