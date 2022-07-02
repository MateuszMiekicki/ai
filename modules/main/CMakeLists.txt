project(main VERSION 0.1.0 LANGUAGES CXX)

set(SOURCE main.cc)
add_executable(${PROJECT_NAME}
        ${SOURCE}
        )
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        )
target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_SOURCE_DIR}/include/knapsack
        )
target_link_libraries(${PROJECT_NAME}
        PRIVATE knapsack::item
        PRIVATE knapsack::bin
        PRIVATE knapsack::algorithm::genetic
        PRIVATE knapsack::algorithm::hill_climbing
        PRIVATE knapsack::algorithm::simulated_annealing
        )
target_compile_options(
        ${PROJECT_NAME}
        PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Release>:${GCC_FLAGS_RELEASE}>>
        PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Debug>:${GCC_FLAGS_DEBUG}>>
)
