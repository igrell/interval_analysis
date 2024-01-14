cmake_minimum_required(VERSION 3.26)
project(interval_analysis)

set(CMAKE_CXX_STANDARD 20)

add_executable(interval_arithmetic interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp  interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp
        covering_relations_analysis/covering_relations.cpp covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp
        mappings/Mapping.h mappings/Henon.h mappings/Rossler.h
        DrawPolicy.h
        sivia_tools/SiviaNode.cpp sivia_tools/SiviaNode.h sivia_tools/sivia.cpp
        exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(interval_arithmetic PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(covering_relations covering_relations_analysis/covering_relations.cpp covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp
        interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp
        mappings/Mapping.h mappings/Henon.h mappings/Rossler.h
        DrawPolicy.h
        exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(covering_relations PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(sivia interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp
        covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp
        DrawPolicy.h
        sivia_tools/SiviaNode.cpp sivia_tools/SiviaNode.h sivia_tools/sivia.cpp
        exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(sivia PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(interval_newton interval_newton.cpp
        autodiff/FAD.cpp autodiff/FAD.h
        interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp
        exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(interval_newton PRIVATE autodiff/ covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(autodiff autodiff/FAD.h autodiff/FAD.cpp
        interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp
        exceptions/EmptyIntersectionException.h)
target_include_directories(autodiff PRIVATE interval_arithmetic_tools/ exceptions/ autodiff/ ./ ${/opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3/})

add_executable(stable_points rootFinder.cpp
        interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp
        covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp
        DrawPolicy.h sivia_tools/SiviaNode.cpp
        sivia_tools/SiviaNode.h
        exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(stable_points PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ ./)

add_executable(manifolds manifold_parametrization_tools/manifolds.cpp
        interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp
        autodiff/FAD.h autodiff/FAD.cpp
        exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h)
target_include_directories(manifolds PRIVATE autodiff/ interval_arithmetic_tools/ exceptions/ ./)

add_executable(testing testing.cpp
        covering_relations_analysis/TSet.h covering_relations_analysis/TSet.cpp
        interval_arithmetic_tools/Interval.h interval_arithmetic_tools/Interval.cpp interval_arithmetic_tools/IPoint.h interval_arithmetic_tools/IPoint.cpp
        mappings/Mapping.h mappings/Henon.h mappings/Rossler.h
        DrawPolicy.h
        exceptions/EmptyIntersectionException.h exceptions/DivisionByZeroIntervalException.h
        autodiff/FAD.h autodiff/FAD.cpp autodiff/TaylorPol.h autodiff/TaylorPol.cpp
        autodiff/TaylorAD.h
)
target_include_directories(testing PRIVATE covering_relations_analysis/ exceptions/ interval_arithmetic_tools/ mappings/ sivia_tools/ autodiff/ ./)
