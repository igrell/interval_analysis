cmake_minimum_required(VERSION 3.26)
project(interval_analysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(interval_arithmetic interval_arithmetic_tools/Interval.h covering_relations_analysis/covering_relations.cpp interval_arithmetic_tools/Interval.cpp mappings/Rossler.h covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp mappings/Mapping.h mappings/Henon.h DrawPolicy.h sivia_tools/SiviaNode.cpp sivia_tools/SiviaNode.h sivia_tools/sivia.cpp exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(interval_arithmetic PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(covering_relations covering_relations_analysis/covering_relations.cpp interval_arithmetic_tools/Interval.h  interval_arithmetic_tools/Interval.cpp mappings/Rossler.h covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp mappings/Mapping.h mappings/Henon.h DrawPolicy.h exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(covering_relations PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(sivia interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp DrawPolicy.h sivia_tools/SiviaNode.cpp sivia_tools/SiviaNode.h sivia_tools/sivia.cpp exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(sivia PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(interval_newton interval_newton.cpp autodiff/Autodiff.cpp autodiff/Autodiff.h interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(interval_newton PRIVATE autodiff/ covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(autodiff autodiff/Autodiff.h autodiff/Autodiff.cpp interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp exceptions/EmptyIntersectionException.h)
target_include_directories(autodiff PRIVATE interval_arithmetic_tools/ exceptions/ autodiff/ ./)

add_executable(stable_points rootFinder.cpp interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp DrawPolicy.h sivia_tools/SiviaNode.cpp sivia_tools/SiviaNode.h exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(stable_points PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)
