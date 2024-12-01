# CMakeLists.txt
cmake_minimum_required(VERSION 3.28)
project(adventofcode, LANGUAGES CXX)

add_executable(adventofcode)

target_sources(adventofcode
    PRIVATE
        main.cpp
)

set_target_properties(adventofcode
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)
