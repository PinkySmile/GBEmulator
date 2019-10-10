cmake_minimum_required(VERSION 3.14)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(GBEmulator src/main.cpp src/CPU.cpp src/CPU.hpp)