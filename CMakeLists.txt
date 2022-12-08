cmake_minimum_required(VERSION 3.22)
project(interval_arithmetic)

set(CMAKE_CXX_STANDARD 20)

add_executable(interval_arithmetic Interval.h covering_relations.cpp Interval.cpp Rossler.cpp Rossler.h TSet.h TSet.cpp IPoint.h IPoint.cpp Mapping.cpp Mapping.h sivia.cpp main.cpp)

