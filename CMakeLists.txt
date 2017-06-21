cmake_minimum_required(VERSION 3.7)
project(Lab_3_4)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fopenmp")

set(SOURCE_FILES main.cpp sequential_matrix_multiplier_test.h matrix_multiplier_test.h parallel_matrix_multiplier_test.h optimized_parallel_matrix_multiplier_test.h)
add_executable(Lab_3_4 ${SOURCE_FILES})