cmake_minimum_required(VERSION 3.20)

project(W9
    VERSION 0.1.0
    DESCRIPTION "W9 JavaScript Engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Engine sources only (بدون main.cpp)

file(GLOB_RECURSE W9_CORE_SOURCES
    engine/*.cpp
)

# Core library

add_library(w9_core STATIC
    ${W9_CORE_SOURCES}
)

target_include_directories(w9_core
    PUBLIC
        include
        engine
)

# Main executable

add_executable(W9
    src/main.cpp
)

target_link_libraries(W9
    PRIVATE
        w9_core
)

# Tests

enable_testing()

add_executable(w9_tests
    tests/test_main.cpp
)

target_link_libraries(w9_tests
    PRIVATE
        w9_core
)

add_test(
    NAME CoreEngineTests
    COMMAND w9_tests
)
