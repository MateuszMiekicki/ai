include(${CMAKE_SOURCE_DIR}/third_party/googletest.cmake)
project(shakashaka_ut LANGUAGES CXX)

add_executable(${PROJECT_NAME} Board_SetCellTest.cc)
target_link_libraries(${PROJECT_NAME}
        PRIVATE GTest::gtest
        PRIVATE GTest::gtest_main
        PRIVATE shakashaka::board
        )
target_include_directories(${PROJECT_NAME} PRIVATE ${gtest_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        )

include(CompilationFlags)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    list(APPEND GCC_FLAGS -DNDEBUG -O3)
    target_compile_options(${PROJECT_NAME} PRIVATE -DNDEBUG -O3)
else ()
    list(APPEND GCC_FLAGS -g3 -O0)
    target_compile_options(${PROJECT_NAME} PRIVATE -g3 -O0)
endif ()

gtest_discover_tests(${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
