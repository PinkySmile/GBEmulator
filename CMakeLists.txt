cmake_minimum_required(VERSION 3.14)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-W -Wall -Wextra)
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
	src/ProcessingUnits/Instructions/CPUInstructions.cpp
	src/ProcessingUnits/Instructions/CPUInstructions.hpp
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
	src/Network/CableInterface.cpp
	src/Timing/Timer.cpp
	src/Timing/Timer.hpp
	src/ProcessingUnits/Instructions/BasicInstructions.cpp
	src/ProcessingUnits/Instructions/BitInstructions.cpp
	src/debugger/debugger.cpp src/debugger/debugger.hpp src/Memory/Cartridge.cpp src/Memory/Cartridge.hpp)

target_link_libraries(
        GBEmulator
        sfml-graphics
        sfml-window
        sfml-system
)

add_executable(
		tests
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
		src/ProcessingUnits/Instructions/CPUInstructions.cpp
		src/ProcessingUnits/Instructions/CPUInstructions.hpp
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
		src/Network/CableInterface.cpp
		src/Timing/Timer.cpp
		src/Timing/Timer.hpp
		src/ProcessingUnits/Instructions/BasicInstructions.cpp
		src/ProcessingUnits/Instructions/BitInstructions.cpp
		src/debugger/debugger.cpp src/debugger/debugger.hpp
		tests/TestComponents.cpp
		tests/TestComponents.hpp
		tests/TestCpuInstruction.cpp)