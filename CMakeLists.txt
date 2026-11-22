cmake_minimum_required(VERSION 3.24)

enable_testing()

if(NOT DEFINED CMAKE_CXX_COMPILER AND "$ENV{CXX}" STREQUAL ""
    AND NOT DEFINED CMAKE_TOOLCHAIN_FILE AND "$ENV{CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    if(CMAKE_HOST_APPLE)
        find_program(GNU_CXX NAMES g++-16 g++-15 g++-14 g++-13 g++-12 g++-11 g++-10 NO_CACHE)
    elseif(CMAKE_HOST_UNIX)
        find_program(GNU_CXX NAMES g++ NO_CACHE)
    endif()

    if(GNU_CXX)
        set(CMAKE_CXX_COMPILER "${GNU_CXX}")
    endif()
endif()

project(GameOfLife
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(GameOfLife
    src/main.cpp
    src/GameOfLife.cpp
)

target_include_directories(GameOfLife
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(StructureTests
    tests/StructureTests.cpp
    src/GameOfLife.cpp
)

target_include_directories(StructureTests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME StructureTests COMMAND StructureTests)
