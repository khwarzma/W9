cmake_minimum_required(VERSION 3.20)

project(W9
    VERSION 0.1.0
    DESCRIPTION "W9 JavaScript Engine"
    LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Compiler warnings

if(MSVC)

    add_compile_options(/W4)

else()

    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )

endif()


# Source files

file(GLOB_RECURSE W9_SOURCES

    engine/*.cpp
    src/*.cpp

)


add_executable(
    W9
    ${W9_SOURCES}
)


target_include_directories(
    W9
    PRIVATE

    include
    engine

)


# Tests

enable_testing()


add_subdirectory(tests OPTIONAL)