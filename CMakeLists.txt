cmake_minimum_required(VERSION 3.14)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)

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
	src/Network/CableInterface.cpp
	src/Network/GbgProtocolNetworkInterface.cpp
	src/Network/GbgProtocolNetworkInterface.hpp
)

target_link_libraries(
        GBEmulator
        sfml-graphics
        sfml-window
        sfml-system
)