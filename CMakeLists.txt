cmake_minimum_required(VERSION 3.22)
project(interval_analysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(interval_arithmetic interval_arithmetic_tools/Interval.h covering_relations_analysis/covering_relations.cpp interval_arithmetic_tools/Interval.cpp mappings/Rossler.h covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp mappings/Mapping.h mappings/Henon.h DrawPolicy.h sivia_tools/SiviaNode.cpp sivia_tools/SiviaNode.h sivia_tools/SiviaGraph.cpp sivia_tools/SiviaGraph.h sivia_tools/sivia.cpp exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)

target_include_directories(interval_arithmetic PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)