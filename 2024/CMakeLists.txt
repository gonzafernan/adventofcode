# CMakeLists.txt
cmake_minimum_required(VERSION 3.28)
project(adventofcode, LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(adventofcode)

target_include_directories(adventofcode
    PRIVATE
        include
)

file(GLOB SOURCES "src/*.cpp")

target_sources(adventofcode
    PRIVATE
        main.cpp
        ${SOURCES}
)

set_target_properties(adventofcode
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)
