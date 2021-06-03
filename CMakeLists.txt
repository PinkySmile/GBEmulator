cmake_minimum_required(VERSION 3.10)
project(GBEmulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/pkgs)

if (NOT MSVC)
	if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
		add_compile_options(-W -Wall -Wextra -Wshadow)
	elseif (WIN32)
		add_link_options(-mwindows)
	endif()
	if (NO_EXCEPTION OR ARDUINO)
		message("Exceptions disabled")
		if (NOT DEBUGGER)
			set(DEBUGGER CMD)
		endif ()
		add_compile_options(-fno-exceptions)
	elseif (NOT DEBUGGER)
		set(DEBUGGER GUI)
	endif ()
endif()

message("Selected Debugger is ${DEBUGGER}")
if (DEBUGGER STREQUAL GUI)
	find_package(SFML REQUIRED)
	find_package(TGUI)
else ()
	find_package(SFML)
	find_package(SDL2)
endif()

if (NO_DISPLAY_THREAD)
	message("Run display in the main thread")
	set(NO_DISPLAY_THREAD 1)
else ()
	set(NO_DISPLAY_THREAD 0)
endif ()

set(SDL_IMPL 0)
set(SFML_IMPL 0)
set(SERENITY_IMPL 0)
set(SPECIFIC_COMPILE_FLAGS standard=std)
if (ARDUINO)
	set(SPECIFIC_COMPILE_FLAGS ARDUINO=1)
	set(ADDITIONAL_SOURCES src/ArduinoStuff/Impl.cpp)
endif()
if (SFML_FOUND)
	include_directories(
		${SFML_INCLUDE_DIRS}
	)
	set(
		JOYPAD_IMPL
		src/Joypad/SfmlKeyboardJoypadEmulator.cpp
		src/Joypad/SfmlKeyboardJoypadEmulator.hpp
	)
	set(
		SOUND_IMPL
		src/Sound/SFMLSoundPlayer.cpp
		src/Sound/SFMLSoundPlayer.hpp
	)
	set(
		LCD_IMPL
		src/LCD/LCDSFML.cpp
		src/LCD/LCDSFML.hpp
	)
	if (NOT NO_EXCEPTION)
		set(
			NETWORK_IMPL
			src/CableLink/BgbProtocolNetworkInterface.cpp
			src/CableLink/BgbProtocolNetworkInterface.hpp
			src/Network/BgbHandler.cpp
		)
	endif ()
	set(SFML_IMPL 1)
	set(
		OTHER_LIBRARIES
		${SFML_GRAPHICS_LIBRARY}
		${SFML_SYSTEM_LIBRARY}
		${SFML_WINDOW_LIBRARY}
		${SFML_NETWORK_LIBRARY}
		${SFML_AUDIO_LIBRARY}
	)
	message("Sfml was found (${SFML_INCLUDE_DIRS} ${SFML_GRAPHICS_LIBRARY} ${SFML_SYSTEM_LIBRARY} ${SFML_WINDOW_LIBRARY} ${SFML_NETWORK_LIBRARY} ${SFML_AUDIO_LIBRARY})")
elseif (SDL2_FOUND)
	include_directories(
		${SDL2_INCLUDE_DIRS}
	)
	set(
		JOYPAD_IMPL
		src/Joypad/SDLKeyboardJoypadEmulator.cpp
		src/Joypad/SDLKeyboardJoypadEmulator.hpp
	)
	set(
		LCD_IMPL
		src/LCD/LCDSDL.cpp
		src/LCD/LCDSDL.hpp
		src/LCD/util/TimerSDL.cpp
		src/LCD/util/TimerSDL.hpp
	)
	set(
		OTHER_LIBRARIES
		${SDL2_LIBRARY}
	)
	set(SDL_IMPL 1)
	message("SDL was found ${SDL2_INCLUDE_DIRS} ${SDL2_LIBRARY}")
elseif (SERENITYOS)
	set(
		LCD_IMPL
		src/LCD/LCDSerenityLibGui.cpp
		src/LCD/LCDSerenityLibGui.hpp
		src/LCD/SerenityPlatformWindow.cpp
		src/LCD/SerenityPlatformWindow.hpp
	)
	set(SERENITY_IMPL 1)
	message("Using SerenityOS native libraries")
else ()
	message(FATAL_ERROR "Cannot find either SDL2 or SFML. Please either set SFML_DIR or SDL2_DIR.")
endif ()

add_library(
	GBEmulator_Core STATIC
	${ADDITIONAL_SOURCES}
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
	src/Timing/Clock.cpp
	src/Timing/Clock.hpp
	src/ProcessingUnits/SoundChannel/IGBSoundChannel.hpp
	src/ProcessingUnits/SoundChannel/SquareWaveChannel.cpp
	src/ProcessingUnits/SoundChannel/SquareWaveChannel.hpp
	src/ProcessingUnits/SoundChannel/BasicSoundChannel.cpp
	src/ProcessingUnits/SoundChannel/BasicSoundChannel.hpp
	src/ProcessingUnits/SoundChannel/ModulableWaveChannel.cpp
	src/ProcessingUnits/SoundChannel/ModulableWaveChannel.hpp
	src/ProcessingUnits/SoundChannel/NoiseWaveChannel.cpp
	src/ProcessingUnits/SoundChannel/NoiseWaveChannel.hpp
)
target_compile_definitions(GBEmulator_Core PRIVATE ${SPECIFIC_COMPILE_FLAGS})

if (DEBUGGER STREQUAL GUI)
	set(DEBUGGER_DEFINE 1)
	set(
		DEBUGGER_SRC
		src/debugger/GUIdebugger.cpp
		src/debugger/GUIdebugger.hpp
		src/Network/BgbHandler.hpp
		src/debugger/CompiledCondition.cpp
		src/debugger/CompiledCondition.hpp
		src/ProcessingUnits/Instructions/Strings.cpp
		src/ProcessingUnits/Instructions/Strings.hpp
		src/ProcessingUnits/Instructions/Strings2.cpp
	)
elseif (DEBUGGER STREQUAL CMD)
	set(DEBUGGER_DEFINE 2)
	set(
		DEBUGGER_SRC
		src/debugger/debugger.cpp
		src/debugger/debugger.hpp
		src/Network/BgbHandler.hpp
		src/debugger/CompiledCondition.cpp
		src/debugger/CompiledCondition.hpp
		src/ProcessingUnits/Instructions/Strings.cpp
		src/ProcessingUnits/Instructions/Strings.hpp
		src/ProcessingUnits/Instructions/Strings2.cpp
	)
else ()
	set(DEBUGGER_DEFINE 2)
	if (NOT ARDUINO)
		set(DEBUGGER_SRC src/ProcessingUnits/Instructions/Strings.cpp src/ProcessingUnits/Instructions/Strings.hpp src/ProcessingUnits/Instructions/Strings2.cpp)
	endif ()
endif()

add_executable(
        GBEmulator
	src/main.cpp
	${JOYPAD_IMPL}
	${SOUND_IMPL}
	${LCD_IMPL}
	${NETWORK_IMPL}
	${DEBUGGER_SRC}
	src/CreateInferfaceImpl.cpp
	src/CreateInferfaceImpl.hpp
	src/DummyDevices.hpp
)
if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
	set(DEBUG_FLAG DEBUG)
else()
	set(DEBUG_FLAG NDEBUG)
endif()

target_compile_definitions(
	GBEmulator PRIVATE
	DEBUGGER=${DEBUGGER_DEFINE}
	SDL_IMPL=${SDL_IMPL}
	SFML_IMPL=${SFML_IMPL}
	SERENITY_IMPL=${SERENITY_IMPL}
	NO_DISPLAY_THREAD=${NO_DISPLAY_THREAD}
	${DEBUG_FLAG}=1
	${SPECIFIC_COMPILE_FLAGS}
)

if (SERENITYOS)
	set(OS_SPEC_LIBS pthread gui gfx core)
elseif (NOT WIN32)
	if (SFML_IMPL)
		set(OS_SPEC_LIBS X11 pthread)
	else ()
		set(OS_SPEC_LIBS pthread)
	endif()
elseif (NOT MSVC)
	set(OS_SPEC_LIBS pthread)
endif ()

target_link_libraries(
	GBEmulator
	${OTHER_LIBRARIES}
	${OS_SPEC_LIBS}
	GBEmulator_Core
)

set(
	TESTS_BASE_SOURCES
	tests/communism.hpp
	tests/TestComponents.cpp
	tests/TestComponents.hpp
)

add_library(
	test_base
	${TESTS_BASE_SOURCES}
)

target_link_libraries(test_base GBEmulator_Core)

add_executable(
	tests_cpuinstr
	tests/TestCPUInstruction/arithmetic/ADC.cpp
	tests/TestCPUInstruction/arithmetic/ADD16.cpp
	tests/TestCPUInstruction/arithmetic/ADD.cpp
	tests/TestCPUInstruction/arithmetic/SBC.cpp
	tests/TestCPUInstruction/bits/RES.cpp
	tests/TestCPUInstruction/bits/RESunrefHL.cpp
	tests/TestCPUInstruction/bits/SET.cpp
	tests/TestCPUInstruction/bits/SETunrefHL.cpp
	tests/TestCPUInstruction/CALL.cpp
	tests/TestCPUInstruction/CALL.cpp
	tests/TestCPUInstruction/DEC.cpp
	tests/TestCPUInstruction/INC.cpp
	tests/TestCPUInstruction/JP.cpp
	tests/TestCPUInstruction/JR.cpp
	tests/TestCPUInstruction/LD.cpp
	tests/TestCPUInstruction/LD/LD8.cpp
	tests/TestCPUInstruction/POP.cpp
	tests/TestCPUInstruction/PUSH.cpp
	tests/TestCPUInstruction/RET.cpp
	tests/TestCPUInstruction/TestCpuInstruction.cpp
)

target_link_libraries(
	tests_cpuinstr
	criterion
	sfml-system
	test_base
)

add_executable(
        tests_gpu
	tests/TestGpu/Test_isStatInterrupt.cpp
	tests/TestGpu/Test_isVBlankInterrupt.cpp
	tests/TestGpu/Test_readVRAM.cpp
	tests/TestGpu/Test_writeVRAM.cpp
)

target_link_libraries(
        tests_gpu
        criterion
	sfml-system
	test_base
)

add_executable(
	tests_misc
	tests/TestCartridge/TestMBC1.cpp
	tests/TestCpu/Test_write.cpp
)

target_link_libraries(
	tests_misc
	criterion
	sfml-system
	test_base
)

add_executable(
	all_tests
	tests/TestCartridge/TestMBC1.cpp
	tests/TestCpu/Test_write.cpp
	tests/TestGpu/Test_isStatInterrupt.cpp
	tests/TestGpu/Test_isVBlankInterrupt.cpp
	tests/TestGpu/Test_readVRAM.cpp
	tests/TestGpu/Test_writeVRAM.cpp
	tests/TestCPUInstruction/arithmetic/ADC.cpp
	tests/TestCPUInstruction/arithmetic/ADD16.cpp
	tests/TestCPUInstruction/arithmetic/ADD.cpp
	tests/TestCPUInstruction/arithmetic/SBC.cpp
	tests/TestCPUInstruction/bits/RES.cpp
	tests/TestCPUInstruction/bits/RESunrefHL.cpp
	tests/TestCPUInstruction/bits/SET.cpp
	tests/TestCPUInstruction/bits/SETunrefHL.cpp
	tests/TestCPUInstruction/CALL.cpp
	tests/TestCPUInstruction/CALL.cpp
	tests/TestCPUInstruction/DEC.cpp
	tests/TestCPUInstruction/INC.cpp
	tests/TestCPUInstruction/JP.cpp
	tests/TestCPUInstruction/JR.cpp
	tests/TestCPUInstruction/LD.cpp
	tests/TestCPUInstruction/LD/LD8.cpp
	tests/TestCPUInstruction/POP.cpp
	tests/TestCPUInstruction/PUSH.cpp
	tests/TestCPUInstruction/RET.cpp
	tests/TestCPUInstruction/TestCpuInstruction.cpp
)

target_link_libraries(
	all_tests
	criterion
	sfml-system
	test_base
)
