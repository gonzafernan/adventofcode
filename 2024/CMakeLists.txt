# CMakeLists.txt
cmake_minimum_required(VERSION 3.28)
project(adventofcode, LANGUAGES CXX)

add_executable(adventofcode)

target_include_directories(adventofcode
    PRIVATE
        include
)

target_sources(adventofcode
    PRIVATE
        main.cpp
        src/day1.cpp
        src/day3.cpp
)

set_target_properties(adventofcode
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)
