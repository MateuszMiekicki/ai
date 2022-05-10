add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

if (${ENABLE_TESTS})
    message(STATUS "Tests have been included for Shakashaka")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif ()