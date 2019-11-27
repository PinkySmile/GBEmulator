cmake_minimum_required(VERSION 3.10)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-W -Wall -Wextra)
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
        src/Network/BgbProtocolNetworkInterface.cpp
        src/Network/BgbProtocolNetworkInterface.hpp
        src/Network/CableInterface.cpp
        src/Network/CableInterface.hpp
        src/ProcessingUnits/APU.cpp
        src/ProcessingUnits/APU.hpp
        src/ProcessingUnits/CPU.cpp
        src/ProcessingUnits/CPU.hpp
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
)

target_link_libraries(
        GBEmulator
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        pthread
)

add_executable(
        tests
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
        src/Network/CableInterface.hpp
        src/Network/BgbProtocolNetworkInterface.cpp
        src/Network/BgbProtocolNetworkInterface.hpp
        src/LCD/ILCD.hpp
        src/LCD/ILCD.cpp
        src/Network/CableInterface.cpp
        src/Timing/Timer.cpp
        src/Timing/Timer.hpp
        src/ProcessingUnits/Instructions/BasicInstructions.cpp
        src/ProcessingUnits/Instructions/BitInstructions.cpp
        tests/TestComponents.cpp
        tests/TestComponents.hpp
        tests/TestCPUInstruction/TestCpuInstruction.cpp
        src/Memory/Cartridge.cpp
        tests/TestCPUInstruction/DEC.cpp
        src/Memory/Cartridge.hpp
        tests/communism.hpp
        tests/TestCPUInstruction/LD.cpp
        tests/TestCPUInstruction/INC.cpp
        tests/TestGpu/Test_readVRAM.cpp
        src/Sound/ISound.hpp
        tests/TestGpu/Test_writeVRAM.cpp
        tests/TestGpu/Test_isStatInterrupt.cpp
        tests/TestGpu/Test_isVBlankInterrupt.cpp
        tests/TestCpu/Test_write.cpp
        tests/TestCPUInstruction/ADD16.cpp
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
        tests/TestCPUInstruction/bits/RESunrefHL.cpp tests/TestCPUInstruction/bits/SETunrefHL.cpp)

target_link_libraries(
        tests
        criterion
)
