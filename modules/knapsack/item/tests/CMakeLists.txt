include(${CMAKE_SOURCE_DIR}/third_party/googletest.cmake)
project(item_ut LANGUAGES CXX)

add_executable(${PROJECT_NAME} Item_sortItemsInContainerTest.cc
        PrepareItems_prepareDataForSolvedTest.cc)
target_link_libraries(${PROJECT_NAME}
        PRIVATE GTest::gtest
        PRIVATE GTest::gtest_main
        PRIVATE knapsack::item
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

#target_compile_options(
#        ${PROJECT_NAME}
#        PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Release>:${GCC_FLAGS_RELEASE}>>
#        PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Debug>:${GCC_FLAGS_DEBUG}>>
#)

gtest_discover_tests(${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)