cmake_minimum_required(VERSION 3.18)
project(knapsack VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
option(BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" ON)

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_BUILD_TYPE Release)
elseif (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_DEBUG_POSTFIX "-debug")
else ()
    message(FATAL_ERROR "Available build types: Debug or Release.")
endif ()

include(coverage)
include(gcc_flags)

option(ENABLE_TESTS "Enable tests" ON)
if (${ENABLE_TESTS})
    include(CTest)
    enable_testing()
endif ()

add_subdirectory(modules)