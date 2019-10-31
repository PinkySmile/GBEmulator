/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestCpuInstruction.cpp
*/

#include "../src/ProcessingUnits/CPU.hpp"
#include <criterion/criterion.h>

GBEmulator::CPU get_cpu() {

	return GBEmulator::CPU(nullptr, nullptr, nullptr, nullptr);
}


//! LD INSTRUCTION

Test(Instuction00, ) {
	GBEmulator::CPU cpu();
}