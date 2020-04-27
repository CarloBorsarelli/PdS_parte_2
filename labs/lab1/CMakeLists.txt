cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp message.h message.cpp DurationLogger.cpp DurationLogger.h MessageStore.cpp MessageStore.h)