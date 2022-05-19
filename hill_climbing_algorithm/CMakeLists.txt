add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (ENABLE_TESTS)
    message(STATUS "Tests have been included for hill_climbing_algorithm")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif ()