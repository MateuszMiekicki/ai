project(board VERSION 0.1.0 LANGUAGES CXX)

set(SOURCE Board.cc
        Cell.cc)
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
add_library(shakashaka::board ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_SOURCE_DIR}/include/shakashaka/board
        )

include(CompilationFlags)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    list(APPEND GCC_FLAGS -DNDEBUG -O3)
    target_compile_options(${PROJECT_NAME} PRIVATE ${GCC_FLAGS})
else ()
    list(APPEND GCC_FLAGS -g3 -O0)
    target_compile_options(${PROJECT_NAME} PRIVATE ${GCC_FLAGS})
endif ()