cmake_minimum_required(VERSION 3.10)

project(atsp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(data_structures algorithms)

set(SOURCES
    main.cpp
    matrixreader.cpp
    algorithms/bf_atsp.cpp
)

add_executable(atsp ${SOURCES})