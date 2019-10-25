cmake_minimum_required(VERSION 3.14)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-W -Wall -Wextra -g -O0)
endif()

add_executable(
        GBEmulator
        src/main.cpp
        src/ProcessingUnits/CPU.cpp
        src/ProcessingUnits/CPU.hpp
        src/ProcessingUnits/APU.cpp
        src/ProcessingUnits/APU.hpp
        src/ProcessingUnits/GPU.cpp
        src/ProcessingUnits/GPU.hpp
        src/Memory/ROM.cpp
        src/Memory/ROM.hpp
        src/Memory/Memory.cpp
        src/Memory/Memory.hpp
        src/ProcessingUnits/CPUInstructions.cpp
        src/ProcessingUnits/CPUInstructions.hpp
        src/ProcessingUnits/StartupCode.cpp
        src/Joypad/JoypadEmulator.hpp
        src/Joypad/SfmlKeyboardJoypadEmulator.cpp
        src/Joypad/SfmlKeyboardJoypadEmulator.hpp
        src/Network/CableInterface.hpp
	src/Network/BgbProtocolNetworkInterface.cpp
	src/Network/BgbProtocolNetworkInterface.hpp
        src/LCD/ILCD.hpp
        src/LCD/LCDSFML.cpp
        src/LCD/LCDSFML.hpp
        src/LCD/ILCD.cpp
	src/Network/CableInterface.cpp src/Timing/Timer.cpp src/Timing/Timer.hpp)

target_link_libraries(
        GBEmulator
        sfml-graphics
        sfml-window
        sfml-system
)