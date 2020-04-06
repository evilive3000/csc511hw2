cmake_minimum_required(VERSION 3.15)
project(grassland)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(grassland
        animal.cpp
        animal.h
        cell.cpp
        cell.h
        event.cpp
        event.h
        grassLand.h
        herbivore.cpp
        herbivore.h
        main.cpp
        zebra.cpp
        zebra.h)
