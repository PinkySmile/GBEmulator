cmake_minimum_required(VERSION 3.10)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/pkgs)
find_package(SFML REQUIRED)
find_package(TGUI)

include_directories(
	${SFML_INCLUDE_DIRS}
)

if (NOT MSVC)
	if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
		add_compile_options(-W -Wall -Wextra -Wshadow)
	elseif (WIN32)
		add_link_options(-mwindows)
	endif()
endif()

add_executable(
        GBEmulator
        src/debugger/debugger.cpp
        src/debugger/debugger.hpp
        src/Joypad/JoypadEmulator.hpp
        src/Joypad/SfmlKeyboardJoypadEmulator.cpp
        src/Joypad/SfmlKeyboardJoypadEmulator.hpp
        src/LCD/ILCD.cpp
        src/LCD/ILCD.hpp
        src/LCD/LCDSFML.cpp
        src/LCD/LCDSFML.hpp
        src/main.cpp
        src/Memory/Cartridge.cpp
        src/Memory/Cartridge.hpp
        src/Memory/Memory.cpp
        src/Memory/Memory.hpp
        src/Memory/ROM.cpp
        src/Memory/ROM.hpp
        src/CableLink/BgbProtocolNetworkInterface.cpp
        src/CableLink/BgbProtocolNetworkInterface.hpp
        src/CableLink/CableInterface.cpp
        src/CableLink/CableInterface.hpp
        src/ProcessingUnits/APU.cpp
        src/ProcessingUnits/APU.hpp
        src/ProcessingUnits/CPU.cpp
        src/ProcessingUnits/CPU.hpp
        src/ProcessingUnits/Instructions/Instructions.hpp
        src/ProcessingUnits/Instructions/CPUInstructions.cpp
        src/ProcessingUnits/Instructions/CPUInstructions.hpp
        src/ProcessingUnits/Instructions/BasicInstructions.cpp
        src/ProcessingUnits/Instructions/BitInstructions.cpp
        src/ProcessingUnits/GPU.cpp
        src/ProcessingUnits/GPU.hpp
        src/ProcessingUnits/StartupCode.cpp
        src/Sound/ISound.hpp
        src/Sound/SoundPlayer.cpp
        src/Sound/SoundPlayer.hpp
        src/Timing/Timer.cpp
        src/Timing/Timer.hpp
        src/Network/BgbHandler.cpp
        src/Network/BgbHandler.hpp
        src/Network/Exception.hpp
        src/Network/ProtocolHandle.hpp
        src/ProcessingUnits/SoundChannel/SoundChannel.hpp
        src/ProcessingUnits/SoundChannel/SoundChannel.cpp
        src/ProcessingUnits/SoundChannel/NoiseChannel.cpp
        src/ProcessingUnits/SoundChannel/NoiseChannel.hpp
        src/ProcessingUnits/SoundChannel/SquareWaveChannel.cpp
        src/ProcessingUnits/SoundChannel/SquareWaveChannel.hpp
        src/ProcessingUnits/SoundChannel/ModulableWaveChannel.cpp
        src/ProcessingUnits/SoundChannel/ModulableWaveChannel.hpp
	src/debugger/CompiledCondition.cpp
	src/debugger/CompiledCondition.hpp
)

if (NOT WIN32)
	set(OS_SPEC_LIBS X11 pthread)
elseif (NOT MSVC)
	set(OS_SPEC_LIBS pthread)
endif (NOT WIN32)

target_link_libraries(
	GBEmulator
	${SFML_GRAPHICS_LIBRARY}
	${SFML_SYSTEM_LIBRARY}
	${SFML_WINDOW_LIBRARY}
	${SFML_NETWORK_LIBRARY}
	${SFML_AUDIO_LIBRARY}
	${OS_SPEC_LIBS}
)

add_executable(
        tests

	src/Joypad/JoypadEmulator.hpp
	src/LCD/ILCD.cpp
	src/LCD/ILCD.hpp
	src/Memory/Cartridge.cpp
	src/Memory/Cartridge.hpp
	src/Memory/Memory.cpp
	src/Memory/Memory.hpp
	src/Memory/ROM.cpp
	src/Memory/ROM.hpp
	src/CableLink/CableInterface.cpp
	src/CableLink/CableInterface.hpp
	src/ProcessingUnits/APU.cpp
	src/ProcessingUnits/APU.hpp
	src/ProcessingUnits/CPU.cpp
	src/ProcessingUnits/CPU.hpp
	src/ProcessingUnits/Instructions/Instructions.hpp
	src/ProcessingUnits/Instructions/CPUInstructions.cpp
	src/ProcessingUnits/Instructions/CPUInstructions.hpp
	src/ProcessingUnits/Instructions/BasicInstructions.cpp
	src/ProcessingUnits/Instructions/BitInstructions.cpp
	src/ProcessingUnits/GPU.cpp
	src/ProcessingUnits/GPU.hpp
	src/ProcessingUnits/StartupCode.cpp
	src/Sound/ISound.hpp
	src/Timing/Timer.cpp
	src/Timing/Timer.hpp
	src/Network/Exception.hpp
	src/Network/ProtocolHandle.hpp
	src/ProcessingUnits/SoundChannel/SoundChannel.hpp
	src/ProcessingUnits/SoundChannel/SoundChannel.cpp
	src/ProcessingUnits/SoundChannel/NoiseChannel.cpp
	src/ProcessingUnits/SoundChannel/NoiseChannel.hpp
	src/ProcessingUnits/SoundChannel/SquareWaveChannel.cpp
	src/ProcessingUnits/SoundChannel/SquareWaveChannel.hpp
	src/ProcessingUnits/SoundChannel/ModulableWaveChannel.cpp
	src/ProcessingUnits/SoundChannel/ModulableWaveChannel.hpp

        tests/TestComponents.cpp
        tests/TestComponents.hpp
        tests/TestCPUInstruction/TestCpuInstruction.cpp
        tests/TestCPUInstruction/DEC.cpp
        tests/communism.hpp
        tests/TestCPUInstruction/LD.cpp
        tests/TestCPUInstruction/INC.cpp
        tests/TestGpu/Test_readVRAM.cpp
        tests/TestGpu/Test_writeVRAM.cpp
        tests/TestGpu/Test_isStatInterrupt.cpp
        tests/TestGpu/Test_isVBlankInterrupt.cpp
        tests/TestCpu/Test_write.cpp
        tests/TestCPUInstruction/arithmetic/ADD16.cpp
        tests/TestCPUInstruction/JP.cpp
        tests/TestCPUInstruction/JR.cpp
        tests/TestCPUInstruction/LD/LD8.cpp
        tests/TestCPUInstruction/PUSH.cpp
        tests/TestCPUInstruction/POP.cpp
        tests/TestCPUInstruction/RET.cpp
        tests/TestCPUInstruction/CALL.cpp
        tests/TestCartridge/TestMBC1.cpp
        tests/TestCPUInstruction/bits/RES.cpp
        tests/TestCPUInstruction/bits/SET.cpp
        tests/TestCPUInstruction/CALL.cpp
        tests/TestCPUInstruction/bits/RESunrefHL.cpp
        tests/TestCPUInstruction/bits/SETunrefHL.cpp
        tests/TestCPUInstruction/arithmetic/ADD.cpp
        tests/TestCPUInstruction/arithmetic/ADC.cpp
        tests/TestCPUInstruction/arithmetic/SBC.cpp
)

target_link_libraries(
        tests
        criterion
	sfml-system
)
