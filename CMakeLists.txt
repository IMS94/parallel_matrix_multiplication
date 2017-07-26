cmake_minimum_required(VERSION 3.5)
project(Lab_3_4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
set(CMAKE_VERBOSE_MAKEFILE ON)

if (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0 -O3 -march=native -mtune=native -funroll-loops -ftree-vectorize -ftree-vectorizer-verbose=1 -ffast-math -fassociative-math")
endif ()

set(SOURCE_FILES
        main.cpp
        matrix_multiplier_test.h
        optimized_parallel_matrix_multiplier_test.h
        parallel_matrix_multiplier_test.h
        sequential_matrix_multiplier_test.h)

add_executable(multiplier ${SOURCE_FILES})