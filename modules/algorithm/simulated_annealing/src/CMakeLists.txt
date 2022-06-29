project(simulated_annealing VERSION 0.1.0 LANGUAGES CXX)

set(SOURCE SimulatedAnnealing.cc)
add_library(${PROJECT_NAME}
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
add_library(knapsack::algorithm::simulated_annealing ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_SOURCE_DIR}/include/knapsack/algorithm/simulated_annealing
        PUBLIC ${CMAKE_SOURCE_DIR}/include/knapsack/algorithm/solver
        )
add_dependencies(${PROJECT_NAME} knapsack::bin)
target_link_libraries(${PROJECT_NAME}
        PUBLIC knapsack::bin
        )
target_compile_options(
        ${PROJECT_NAME}
        PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Release>:${GCC_FLAGS_RELEASE}>>
        PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Debug>:${GCC_FLAGS_DEBUG}>>
)
