project(hill_climbing_algorithm VERSION 0.1.0 LANGUAGES CXX)
aux_source_directory(. SOURCE)

add_executable(${PROJECT_NAME} ${SOURCE})

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
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include
        )

include(CompilationFlags)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (MSVC)
    else ()
        target_compile_options(${PROJECT_NAME} PRIVATE ${GCC_FLAGS})
    endif ()
else ()
    if (MSVC)
    else ()
        list(APPEND GCC_FLAGS -g3 -DNDEBUG)
        target_compile_options(${PROJECT_NAME} PRIVATE ${GCC_FLAGS})
    endif ()
endif ()

