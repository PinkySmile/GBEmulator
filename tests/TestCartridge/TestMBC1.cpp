/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestMBC1.cpp
*/

#include <criterion/criterion.h>
#include <random>
#include "../communism.hpp"
#include "../TestComponents.hpp"
#include "../../src/Memory/Cartridge.hpp"

Test(MBC1, ram_extend_switch) {
	Tests::GBTest gb;

	gb.cpu._rom._rom.setMemory(new unsigned char[0x200000], 0x200000);
	gb.cpu._rom._rom.setBankSize(ROM_BANK_SIZE);
	gb.cpu._rom._type = GBEmulator::Memory::Cartridge::MBC1;

	for (unsigned i = 0; i < 0x100; i++) {
		gb.cpu._rom.write(0x6000, i);
		if (i % 2)
			cr_assert(gb.cpu._rom._ramExtended, "Ram extended should be enabled when when writing %d to 0x6000", i);
		else
			cr_assert_not(gb.cpu._rom._ramExtended, "Ram extended shouldn't be enabled when when writing %d to 0x6000", i);
	}
}

Test(MBC1, rom_bank_switch) {
	Tests::GBTest gb;

	gb.cpu._rom._rom.setMemory(new unsigned char[0x200000], 0x200000);
	gb.cpu._rom._rom.setBankSize(ROM_BANK_SIZE);
	gb.cpu._rom._type = GBEmulator::Memory::Cartridge::MBC1;

	gb.cpu._rom.write(0x6000, 1);
	cr_assert(gb.cpu._rom._ramExtended, "Ram extended should be enabled when when writing 1 to 0x6000");
	for (unsigned i = 0; i < 0x100; i++) {
		gb.cpu._rom.write(0x2000, i);
		gb.cpu._rom.write(0x4000, i >> 5U);
		cr_assert_eq(gb.cpu._rom._rom.getCurrentBank(), (i % 0x20) + (i % 0x20 == 0), "Rom bank should be %d but was %d", (i % 0x20) + (i % 0x20 == 0), gb.cpu._rom._rom.getCurrentBank());
	}

	gb.cpu._rom.write(0x6000, 0);
	cr_assert_not(gb.cpu._rom._ramExtended, "Ram extended shouldn't be enabled when when writing 0 to 0x6000");
	for (unsigned i = 0; i < 0x100; i++) {
		gb.cpu._rom.write(0x2000, i);
		gb.cpu._rom.write(0x4000, i >> 5U);
		cr_assert_eq(gb.cpu._rom._rom.getCurrentBank(), (i % 0x80) + (i % 0x20 == 0), "Rom bank should be %d but was %d", (i % 0x80) + (i % 0x20 == 0), gb.cpu._rom._rom.getCurrentBank());
	}
}

Test(MBC1, rom_bank_mapping) {
	Tests::GBTest gb;
	auto mem = new unsigned char[0x200000];

	gb.cpu._rom._rom.setMemory(mem, 0x200000);
	gb.cpu._rom._rom.setBankSize(ROM_BANK_SIZE);
	gb.cpu._rom._type = GBEmulator::Memory::Cartridge::MBC1;

	for (int i = 0; i < (0x200000 / 0x4000); i++)
		mem[i * 0x4000] = i;

	gb.cpu._rom.write(0x6000, 1);
	for (unsigned i = 0; i < (0x200000 / 0x4000); i++) {
		gb.cpu._rom.write(0x2000, i);
		gb.cpu._rom.write(0x4000, i >> 5U);
		cr_assert_eq(gb.cpu._rom.read(0x4000), i % 0x20 + (i % 0x20 == 0), "Rom data at 0x4000 with bank %d should be 0x%X but was 0x%X", i, i % 0x20 + (i % 0x20 == 0), gb.cpu._rom.read(0x4000));
	}

	gb.cpu._rom.write(0x6000, 0);
	for (unsigned i = 0; i < (0x200000 / 0x4000); i++) {
		gb.cpu._rom.write(0x2000, i);
		gb.cpu._rom.write(0x4000, i >> 5U);
		cr_assert_eq(gb.cpu._rom.read(0x4000), i + (i % 0x20 == 0), "Rom data at 0x4000 with bank %d should be 0x%X but was 0x%X", i, i + (i % 0x20 == 0), gb.cpu._rom.read(0x4000));
	}
}

Test(MBC1, ram_bank_switch) {
	Tests::GBTest gb;
	auto mem = new unsigned char[0x8000];
	std::random_device rand;

	gb.cpu._rom._rom.setMemory(new unsigned char[1], 1);
	gb.cpu._rom._rom.setBankSize(1);
	gb.cpu._rom._type = GBEmulator::Memory::Cartridge::MBC1_RAM;

	gb.cpu._rom._ram.setMemory(mem, RAM_BANKING_SIZE * 4);
	gb.cpu._rom._ram.setBankSize(RAM_BANKING_SIZE);

	gb.cpu._rom.write(0x6000, 1);
	cr_assert(gb.cpu._rom._ramExtended, "Ram extended should be enabled when when writing 1 to 0x6000");
	for (unsigned i = 0; i < 0x100; i++) {
		gb.cpu._rom.write(0x4000, i);
		cr_assert_eq(gb.cpu._rom._ram.getCurrentBank(), i & 0b11U, "Rom RAM bank should be %d but was %d", i & 0b11U, gb.cpu._rom._rom.getCurrentBank());
	}

	gb.cpu._rom.write(0x6000, 0);
	cr_assert_not(gb.cpu._rom._ramExtended, "Ram extended shouldn't be enabled when when writing 0 to 0x6000");
	for (unsigned i = 0; i < 0x100; i++) {
		unsigned char val = rand() & 0b11U;

		gb.cpu._rom._ram.setBank(val);
		gb.cpu._rom.write(0x4000, i);
		cr_assert_eq(gb.cpu._rom._ram.getCurrentBank(), val, "Rom RAM bank should be %d but was %d", val, gb.cpu._rom._rom.getCurrentBank());
	}
}

Test(MBC1, ram_bank_mapping) {
	Tests::GBTest gb;
	auto mem = new unsigned char[RAM_BANKING_SIZE * 4];

	gb.cpu._rom._type = GBEmulator::Memory::Cartridge::MBC1_RAM;

	gb.cpu._rom._ram.setMemory(mem, RAM_BANKING_SIZE * 4);
	gb.cpu._rom._ram.setBankSize(RAM_BANKING_SIZE);

	for (int i = 0; i < 4; i++)
		mem[RAM_BANKING_SIZE * i] = i;

	gb.cpu._rom.write(0x6000, 1);
	for (unsigned i = 0; i < 4; i++) {
		gb.cpu._rom.write(0x4000, i);
		cr_assert_eq(gb.cpu._rom.read(0xA000), i, "Rom RAM data at 0xA000 with bank %d should be 0x%X but was 0x%X", i, i, gb.cpu._rom.read(0xA000));
	}
}

Test(MBC1, tricky_rom_bank_switch) {
	Tests::GBTest gb;
	std::random_device rand;

	gb.cpu._rom._rom.setMemory(new unsigned char[0x200000], 0x200000);
	gb.cpu._rom._rom.setBankSize(ROM_BANK_SIZE);
	gb.cpu._rom._type = GBEmulator::Memory::Cartridge::MBC1;

	for (unsigned i = 0; i < 0x100; i++) {
		bool extend = rand() % 2;

		gb.cpu._rom.write(0x6000, extend);
		gb.cpu._rom.write(0x4000, i >> 5U);
		gb.cpu._rom.write(0x2000, i);
		cr_assert_eq(
			gb.cpu._rom._rom.getCurrentBank(),
			(i % (extend ? 0x20 : 0x80)) + (i % 0x20 == 0),

			"Rom bank should be %d but was %d (with index %d and ram extended %s)",
			(i % (extend ? 0x20 : 0x80)) + (i % 0x20 == 0),
			gb.cpu._rom._rom.getCurrentBank(),
			i,
			extend ? "true" : "false"
		);
	}
}

Test(MBC1, tricky_ram_bank_switch) {
	Tests::GBTest gb;
	auto mem = new unsigned char[0x8000];
	std::random_device rand;

	gb.cpu._rom._rom.setMemory(new unsigned char[1], 1);
	gb.cpu._rom._rom.setBankSize(1);
	gb.cpu._rom._type = GBEmulator::Memory::Cartridge::MBC1_RAM;

	gb.cpu._rom._ram.setMemory(mem, RAM_BANKING_SIZE * 4);
	gb.cpu._rom._ram.setBankSize(RAM_BANKING_SIZE);

	for (int i = 0; i < 4; i++)
		mem[RAM_BANKING_SIZE * i] = i;

	for (unsigned i = 0; i < 0x100; i++) {
		bool extend = rand() % 2;

		gb.cpu._rom.write(0x6000, extend);
		gb.cpu._rom.write(0x4000, i);
		cr_assert_eq(
			gb.cpu._rom.read(0xA000),
			extend ? i & 0b11U : 0,

			"Rom RAM bank should be %d but was %d (with index %d and ram extended %s)",
			extend ? i & 0b11U : 0,
			gb.cpu._rom.read(0xA000),
			i,
			extend ? "true" : "false");
	}
}
