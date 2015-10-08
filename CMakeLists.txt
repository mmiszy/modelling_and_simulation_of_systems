cmake_minimum_required(VERSION 3.2)
project(modelling_and_simulation_of_systems)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lgmpxx -lgmp -Wall -O3")

set(SOURCE_FILES
    main.cpp)

add_executable(modelling_and_simulation_of_systems ${SOURCE_FILES})