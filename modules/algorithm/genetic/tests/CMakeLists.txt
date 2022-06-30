include(${CMAKE_SOURCE_DIR}/third_party/googletest.cmake)
project(genetic_ut LANGUAGES CXX)

add_executable(${PROJECT_NAME} Genetic_solveProblemWithExampleDataSet.cc)
target_link_libraries(${PROJECT_NAME}
        PRIVATE GTest::gtest
        PRIVATE GTest::gtest_main
        PRIVATE knapsack::bin
        PRIVATE knapsack::algorithm::genetic
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
gtest_discover_tests(${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)