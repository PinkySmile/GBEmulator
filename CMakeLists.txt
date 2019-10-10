cmake_minimum_required(VERSION 3.14)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(GBEmulator src/main.cpp src/ProcessingUnits/CPU.cpp src/ProcessingUnits/CPU.hpp src/ProcessingUnits/APU.cpp src/ProcessingUnits/APU.hpp src/ProcessingUnits/GPU.cpp src/ProcessingUnits/GPU.hpp src/Memory/ROM.cpp src/Memory/ROM.hpp src/Memory/Memory.cpp src/Memory/Memory.hpp)