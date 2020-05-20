# cmake_minimum_required(VERSION <specify CMake version here>)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3 main.cpp ResultT.cpp ResultT.h MapperInputT.cpp MapperInputT.h ReducerInputT.cpp ReducerInputT.h CoordinatorT.cpp CoordinatorT.h DurationLogger.cpp DurationLogger.h)