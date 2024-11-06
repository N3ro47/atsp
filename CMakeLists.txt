cmake_minimum_required(VERSION 3.10)

project(atsp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(algorithms utils)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")#-Wall -g


set(SOURCES
    main.cpp
    matrixreader.cpp
    algorithms/bf_atsp.cpp
    algorithms/bb_atsp.cpp
    algorithms/sa_atsp.cpp
    menu.cpp
)

add_executable(atsp ${SOURCES})
