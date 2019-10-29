/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CPU_Instructions.c
*/

#include "CPUInstructions.hpp"
#include "CPU.hpp"

namespace GBEmulator::Instructions
{
	const std::function<unsigned char (CPU &, CPU::Registers &)> _bitLevelInstructions[256] = {
		//! 0
		{},

		//! 1
		{},

		//! 2
		{},

		//! 3
		{},

		//! 4
		{},

		//! 5
		{},

		//! 6
		{},

		//! 7
		{},

		//! 8
		{},

		//! 9
		{},

		//! A
		{},

		//! B
		{},

		//! C
		{},

		//! D
		{},

		//! E
		{},

		//! F
		{},

		//! 10
		{},

		//! 11; RL c
		[](CPU &, CPU::Registers &reg){ return RL(reg, reg.c); },

		//! 12
		{},

		//! 13
		{},

		//! 14
		{},

		//! 15
		{},

		//! 16
		{},

		//! 17
		{},

		//! 18
		{},

		//! 19
		{},

		//! 1A
		{},

		//! 1B
		{},

		//! 1C
		{},

		//! 1D
		{},

		//! 1E
		{},

		//! 1F
		{},

		//! 20
		{},

		//! 21
		{},

		//! 22
		{},

		//! 23
		{},

		//! 24
		{},

		//! 25
		{},

		//! 26
		{},

		//! 27
		{},

		//! 28
		{},

		//! 29
		{},

		//! 2A
		{},

		//! 2B
		{},

		//! 2C
		{},

		//! 2D
		{},

		//! 2E
		{},

		//! 2F
		{},

		//! 30
		{},

		//! 31
		{},

		//! 32
		{},

		//! 33
		{},

		//! 34
		{},

		//! 35
		{},

		//! 36
		{},

		//! 37
		{},

		//! 38
		{},

		//! 39
		{},

		//! 3A
		{},

		//! 3B
		{},

		//! 3C
		{},

		//! 3D
		{},

		//! 3E
		{},

		//! 3F
		{},

		//! 40
		{},

		//! 41
		{},

		//! 42
		{},

		//! 43
		{},

		//! 44
		{},

		//! 45
		{},

		//! 46
		{},

		//! 47
		{},

		//! 48
		{},

		//! 49
		{},

		//! 4A
		{},

		//! 4B
		{},

		//! 4C
		{},

		//! 4D
		{},

		//! 4E
		{},

		//! 4F; BIT 1,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 1); },

		//! 50
		{},

		//! 51
		{},

		//! 52
		{},

		//! 53
		{},

		//! 54
		{},

		//! 55
		{},

		//! 56
		{},

		//! 57
		{},

		//! 58
		{},

		//! 59
		{},

		//! 5A
		{},

		//! 5B
		{},

		//! 5C
		{},

		//! 5D
		{},

		//! 5E
		{},

		//! 5F
		{},

		//! 60
		{},

		//! 61
		{},

		//! 62
		{},

		//! 63
		{},

		//! 64
		{},

		//! 65
		{},

		//! 66
		{},

		//! 67
		{},

		//! 68
		{},

		//! 69
		{},

		//! 6A
		{},

		//! 6B
		{},

		//! 6C
		{},

		//! 6D
		{},

		//! 6E
		{},

		//! 6F
		{},

		//! 70
		{},

		//! 71
		{},

		//! 72
		{},

		//! 73
		{},

		//! 74
		{},

		//! 75
		{},

		//! 76
		{},

		//! 77; BIT 6,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 6); },

		//! 78
		{},

		//! 79
		{},

		//! 7A
		{},

		//! 7B
		{},

		//! 7C; BIT 7,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 7); },

		//! 7D
		{},

		//! 7E
		{},

		//! 7F
		{},

		//! 80
		{},

		//! 81
		{},

		//! 82
		{},

		//! 83
		{},

		//! 84
		{},

		//! 85
		{},

		//! 86
		{},

		//! 87
		[](CPU &, CPU::Registers &reg) { return RES(reg.a, 0); },

		//! 88
		{},

		//! 89
		{},

		//! 8A
		{},

		//! 8B
		{},

		//! 8C
		{},

		//! 8D
		{},

		//! 8E
		{},

		//! 8F
		{},

		//! 90
		{},

		//! 91
		{},

		//! 92
		{},

		//! 93
		{},

		//! 94
		{},

		//! 95
		{},

		//! 96
		{},

		//! 97
		{},

		//! 98
		{},

		//! 99
		{},

		//! 9A
		{},

		//! 9B
		{},

		//! 9C
		{},

		//! 9D
		{},

		//! 9E
		{},

		//! 9F
		{},

		//! A0
		{},

		//! A1
		{},

		//! A2
		{},

		//! A3
		{},

		//! A4
		{},

		//! A5
		{},

		//! A6
		{},

		//! A7
		{},

		//! A8
		{},

		//! A9
		{},

		//! AA
		{},

		//! AB
		{},

		//! AC
		{},

		//! AD
		{},

		//! AE
		{},

		//! AF
		{},

		//! B0
		{},

		//! B1
		{},

		//! B2
		{},

		//! B3
		{},

		//! B4
		{},

		//! B5
		{},

		//! B6
		{},

		//! B7
		{},

		//! B8
		{},

		//! B9
		{},

		//! BA
		{},

		//! BB
		{},

		//! BC
		{},

		//! BD
		{},

		//! BE
		{},

		//! BF
		{},

		//! C0
		{},

		//! C1
		{},

		//! C2
		{},

		//! C3
		{},

		//! C4
		{},

		//! C5
		{},

		//! C6
		{},

		//! C7
		{},

		//! C8
		{},

		//! C9
		{},

		//! CA
		{},

		//! CB
		{},

		//! CC
		{},

		//! CD
		{},

		//! CE
		{},

		//! CF
		{},

		//! D0
		{},

		//! D1
		{},

		//! D2
		{},

		//! D3
		{},

		//! D4
		{},

		//! D5
		{},

		//! D6
		{},

		//! D7
		{},

		//! D8
		{},

		//! D9
		{},

		//! DA
		{},

		//! DB
		{},

		//! DC
		{},

		//! DD
		{},

		//! DE
		{},

		//! DF
		{},

		//! E0
		{},

		//! E1
		{},

		//! E2
		{},

		//! E3
		{},

		//! E4
		{},

		//! E5
		{},

		//! E6
		{},

		//! E7
		{},

		//! E8
		{},

		//! E9
		{},

		//! EA
		{},

		//! EB
		{},

		//! EC
		{},

		//! ED
		{},

		//! EE
		{},

		//! EF
		{},

		//! F0
		{},

		//! F1
		{},

		//! F2
		{},

		//! F3
		{},

		//! F4
		{},

		//! F5
		{},

		//! F6
		{},

		//! F7
		{},

		//! F8
		{},

		//! F9
		{},

		//! FA
		{},

		//! FB
		{},

		//! FC
		{},

		//! FD
		{},

		//! FE
		{},

		//! FF
		{}
	};

	const std::function<unsigned char (CPU &, CPU::Registers &)> _instructions[256] = {
		//! 00; NOP: do nothing
		[](CPU &, CPU::Registers &) { return NOP_CYCLE_DURATION; },

		//! 01; LD bc,**: Loads ** into bc.
		[](CPU &cpu, CPU::Registers &reg) { return LD16(reg.bc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! 02; LD (bc), a: Stores a into the memory location pointed to by bc
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.bc, reg.a); },

		//! 03; INC bc: Adds one to bc.
		[](CPU &, CPU::Registers &reg) { return INC16(reg.bc); },

		//! 04; INC b: Adds one to b.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.b); },

		//! 05; DEC b: Subtracts one from b.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.b); },

		//! 06; LD b,*: Loads * into b.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.b, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 07; RLCA: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		{},

		//! 08; LD (**), SP: Load the value pointed to by sp to **
		[](CPU &cpu, CPU::Registers &reg) { return LD16toPTR(cpu, cpu.fetchArgument16(), reg.sp) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! 09; ADD hl,bc: The value of bc is added to hl.
		[](CPU &, CPU::Registers &reg) { return ADD16(reg, reg.hl, reg.bc); },

		//! 0A; LD a,(bc): Loads the value pointed to by bc into a.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, reg.bc); },

		//! 0B; DEC bc: Subtracts one from bc.
		[](CPU &, CPU::Registers &reg) { return DEC16(reg.bc); },

		//! 0C; INC c: Adds one to c.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.c); },

		//! 0D; DEC c: Subtracts one from c.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.c); },

		//! 0E; LD c,*: Loads * into c.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.c, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 0F; RRCA: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		{},

		//! 10; STOP: --
		{},

		//! 11; LD de,**: Loads ** into de.
		[](CPU &cpu, CPU::Registers &reg) { return LD16(reg.de, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! 12; LD (de),a: Stores a into the memory location pointed to by de.
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.de, reg.a); },

		//! 13; INC de: Adds one to de.
		[](CPU &, CPU::Registers &reg) { return INC16(reg.de); },

		//! 14; INC d: Adds one to d.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.d); },

		//! 15; DEC d: Subtracts one from d.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.d); },

		//! 16; LD d,*: Loads * into d.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.d, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 17; RLA: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		[](CPU &, CPU::Registers &reg){ return RL(reg, reg.a); },

		//! 18; JR *: The signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		[](CPU &cpu, CPU::Registers &reg){ return JR(reg, true, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 19; ADD hl,de: The value of de is added to hl.
		[](CPU &, CPU::Registers &reg){ return ADD16(reg, reg.hl, reg.de); },

		//! 1A; LD a,(de): Loads the value pointed to by de into a.
		[](CPU &cpu, CPU::Registers &reg){ return LD8fromPTR(cpu, reg.a, reg.de); },

		//! 1B; DEC de: Subtracts one from de.
		[](CPU &, CPU::Registers &reg){ return DEC16(reg.de); },

		//! 1C; INC e: Adds one to e.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.e); },

		//! 1D; DEC e: Subtracts one from e.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.e); },

		//! 1E; LD e,*: Loads * into e.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.e, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 1F; RRA: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		{},

		//! 20; JR nz,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		[](CPU &cpu, CPU::Registers &reg) { return JR(reg, !reg.fz, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 21; LD hl, **: Loads ** into hl register
		[](CPU &cpu, CPU::Registers &reg) { return LD16(reg.hl, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! 22; LDI (hl),a: Loads a to the address pointed to by hl and increment hl
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl++, reg.a); },

		//! 23; INC hl: Adds one to hl.
		[](CPU &, CPU::Registers &reg) { return INC16(reg.hl); },

		//! 24; INC h: Adds one to h.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.h); },

		//! 25; DEC h: Subtracts one from h.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.h); },

		//! 26; LD h,*: Loads * into h.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.h, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 27; DAA: Adjusts a for BCD addition and subtraction operations.
		{},

		//! 28; JR z,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		[](CPU &cpu, CPU::Registers &reg) { return JR(reg, reg.fz, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 29; ADD hl,hl: The value of hl is added to hl.
		[](CPU &, CPU::Registers &reg) { return ADD16(reg, reg.hl, reg.hl); },

		//! 2A; LDI a,(hl): Loads the value pointed to by hl to a and increments hl
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, reg.hl); },

		//! 2B; DEC hl: Subtracts one from hl.
		[](CPU &, CPU::Registers &reg) { return DEC16(reg.hl); },

		//! 2C; INC l: Adds one to l.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.l); },

		//! 2D; DEC l: Subtracts one from l.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.l); },

		//! 2E; LD l,*: Loads * into l.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.l, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 2F; CPL: The contents of a are inverted (one's complement).
		{},

		//! 30; JR nc,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		{},

		//! 31; LD sp, **: Loads ** into sp register
		[](CPU &cpu, CPU::Registers &reg) { return LD16(reg.sp, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! 32; LD (hl-), a: Loads a into address pointed to by hl and decrement hl
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl--, reg.a); },

		//! 33; INC sp: Adds one to sp.
		[](CPU &, CPU::Registers &reg) { return INC16(reg.sp); },

		//! 34; INC (hl): Adds one to (hl).
		[](CPU &cpu, CPU::Registers &reg) { return INCPTR(cpu, reg, reg.hl); },

		//! 35; DEC (hl): Subtracts one from (hl).
		[](CPU &cpu, CPU::Registers &reg) { return DECPTR(cpu, reg, reg.hl); },

		//! 36; LD (hl),*: Loads * into (hl).
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 37; SCF: Sets the carry flag.
		{},

		//! 38; JR c,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		{},

		//! 39; ADD hl,sp: The value of hl is added to hl.
		[](CPU &, CPU::Registers &reg) { return ADD16(reg, reg.hl, reg.sp); },

		//! 3A; LDD a,(hl): Load the value pointed to by hl to a and decrements hl
		{},

		//! 3B; DEC sp: Subtracts one from sp.
		[](CPU &, CPU::Registers &reg) { return DEC16(reg.sp); },

		//! 3C; INC a: Adds one to a.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.a); },

		//! 3D; DEC a: Subtracts one from a.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.a); },

		//! 3E; LD a,*: Loads * into a.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.a, cpu.fetchArgument()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! 3F; CCF: Inverts the carry flag.
		{},

		//! 40; LD b,b: The contents of b are loaded into b.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.b, reg.b); },

		//! 41; LD b,c: The contents of c are loaded into b.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.b, reg.c); },

		//! 42; LD b,d: The contents of d are loaded into b.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.b, reg.d); },

		//! 43; LD b,e: The contents of e are loaded into b.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.b, reg.e); },

		//! 44; LD b,h: The contents of h are loaded into b.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.b, reg.h); },

		//! 45; LD b,l: The contents of l are loaded into b.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.b, reg.l); },

		//! 46; LD b,(hl): The contents of (hl) are loaded into b.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.b, reg.hl); },

		//! 47; LD b,a: The contents of a are loaded into b.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.b, reg.a); },

		//! 48; LD c,b: The contents of b are loaded into c.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.c, reg.b); },

		//! 49; LD c,c: The contents of c are loaded into c.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.c, reg.c); },

		//! 4A; LD c,d: The contents of d are loaded into c.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.c, reg.d); },

		//! 4B; LD c,e: The contents of e are loaded into c.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.c, reg.e); },

		//! 4C; LD c,h: The contents of h are loaded into c.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.c, reg.h); },

		//! 4D; LD c,l: The contents of l are loaded into c.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.c, reg.l); },

		//! 4E; LD c,(hl): The contents of (hl) are loaded into c.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.c, reg.hl); },

		//! 4F; LD c,a: The contents of a are loaded into c.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.c, reg.a); },

		//! 50; LD d,b: The contents of b are loaded into d.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.d, reg.b); },

		//! 51; LD d,c: The contents of c are loaded into d.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.d, reg.c); },

		//! 52; LD d,d: The contents of d are loaded into d.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.d, reg.d); },

		//! 53; LD d,e: The contents of e are loaded into d.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.d, reg.e); },

		//! 54; LD d,h: The contents of h are loaded into d.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.d, reg.h); },

		//! 55; LD d,l: The contents of l are loaded into d.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.d, reg.l); },

		//! 56; LD d,(hl): The contents of (hl) are loaded into d.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.d, reg.hl); },

		//! 57; LD d,a: The contents of a are loaded into d.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.d, reg.a); },

		//! 58; LD e,b: The contents of b are loaded into e.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.e, reg.b); },

		//! 59; LD e,c: The contents of c are loaded into e.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.e, reg.c); },

		//! 5A; LD e,d: The contents of d are loaded into e.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.e, reg.d); },

		//! 5B; LD e,e: The contents of e are loaded into e.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.e, reg.e); },

		//! 5C; LD e,h: The contents of h are loaded into e.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.e, reg.h); },

		//! 5D; LD e,l: The contents of l are loaded into e.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.e, reg.l); },

		//! 5E; LD e,(hl): The contents of (hl) are loaded into e.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.e, reg.hl); },

		//! 5F; LD e,a: The contents of a are loaded into e.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.e, reg.a); },

		//! 60; LD h,b: The contents of b are loaded into h.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.h, reg.b); },

		//! 61; LD h,c: The contents of c are loaded into h.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.h, reg.c); },

		//! 62; LD h,d: The contents of d are loaded into h.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.h, reg.d); },

		//! 63; LD h,e: The contents of e are loaded into h.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.h, reg.e); },

		//! 64; LD h,h: The contents of h are loaded into h.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.h, reg.h); },

		//! 65; LD h,l: The contents of l are loaded into h.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.h, reg.l); },

		//! 66; LD h,(hl): The contents of (hl) are loaded into h.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.h, reg.hl); },

		//! 67; LD h,a: The contents of a are loaded into h.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.h, reg.a); },

		//! 68; LD l,b: The contents of b are loaded into l.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.l, reg.b); },

		//! 69; LD l,c: The contents of c are loaded into l.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.l, reg.c); },

		//! 6A; LD l,d: The contents of d are loaded into l.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.l, reg.d); },

		//! 6B; LD l,e: The contents of e are loaded into l.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.l, reg.e); },

		//! 6C; LD l,h: The contents of h are loaded into l.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.l, reg.h); },

		//! 6D; LD l,l: The contents of l are loaded into l.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.l, reg.l); },

		//! 6E; LD l,(hl): The contents of (hl) are loaded into l.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.l, reg.hl); },

		//! 6F; LD l,a: The contents of a are loaded into l.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.l, reg.a); },

		//! 70; LD (hl),b: The contents of b are loaded into (hl).
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl, reg.b); },

		//! 71; LD (hl),c: The contents of c are loaded into (hl).
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl, reg.c); },

		//! 72; LD (hl),d: The contents of d are loaded into (hl).
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl, reg.d); },

		//! 73; LD (hl),e: The contents of e are loaded into (hl).
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl, reg.e); },

		//! 74; LD (hl),h: The contents of h are loaded into (hl).
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl, reg.h); },

		//! 75; LD (hl),l: The contents of l are loaded into (hl).
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl, reg.l); },

		//! 76; HALT: Suspends CPU operation until an interrupt or reset occurs.
		[](CPU &cpu, CPU::Registers &) { return cpu.halt(), LD_CYCLE_DURATION; },

		//! 77; LD (hl),a: The contents of a are loaded into (hl).
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.hl, reg.a); },

		//! 78; LD a,b: The contents of b are loaded into a.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.a, reg.b); },

		//! 79; LD a,c: The contents of c are loaded into a.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.a, reg.c); },

		//! 7A; LD a,d: The contents of d are loaded into a.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.a, reg.d); },

		//! 7B; LD a,e: The contents of e are loaded into a.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.a, reg.e); },

		//! 7C; LD a,h: The contents of h are loaded into a.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.a, reg.h); },

		//! 7D; LD a,l: The contents of l are loaded into a.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.a, reg.l); },

		//! 7E; LD a,(hl): The contents of (hl) are loaded into a.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, reg.hl); },

		//! 7F; LD a,a: The contents of a are loaded into a.
		[](CPU &, CPU::Registers &reg) { return LD8(reg.a, reg.a); },

		//! 80; ADD a,b: Adds b to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.b); },

		//! 81; ADD a,c: Adds c to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.c); },

		//! 82; ADD a,d: Adds d to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.d); },

		//! 83; ADD a,e: Adds e to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.e); },

		//! 84; ADD a,h: Adds h to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.h); },

		//! 85; ADD a,l: Adds l to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.l); },

		//! 86; ADD a,(hl): Adds (hl) to a.
		[](CPU &cpu, CPU::Registers &reg) { return ADD8(reg, reg.a, cpu.read(reg.hl)) + INDIRECTION_CYLCE_DURATION; },

		//! 87; ADD a,a: Adds a to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.a); },

		//! 88; ADC a,b: Adds b and the carry flag to a.
		{},

		//! 89; ADC a,c: Adds c and the carry flag to a.
		{},

		//! 8A; ADC a,d: Adds d and the carry flag to a.
		{},

		//! 8B; ADC a,e: Adds e and the carry flag to a.
		{},

		//! 8C; ADC a,h: Adds h and the carry flag to a.
		{},

		//! 8D; ADC a,l: Adds l and the carry flag to a.
		{},

		//! 8E; ADC a,(hl): Adds (hl) and the carry flag to a.
		{},

		//! 8F; ADC a,a: Adds a and the carry flag to a.
		{},

		//! 90; SUB b: Subtracts b from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.b); },

		//! 91; SUB c: Subtracts c from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.c); },

		//! 92; SUB d: Subtracts d from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.d); },

		//! 93; SUB e: Subtracts e from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.e); },

		//! 94; SUB h: Subtracts h from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.h); },

		//! 95; SUB l: Subtracts l from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.l); },

		//! 96; SUB (hl): Subtracts (hl) from a.
		[](CPU &cpu, CPU::Registers &reg) { return SUB8(reg, reg.a, cpu.read(reg.hl)) + INDIRECTION_CYLCE_DURATION; },

		//! 97; SUB a: Subtracts a from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.a); },

		//! 98; SBC a,b: Subtracts b and the carry flag from a.
		{},

		//! 99; SBC a,c: Subtracts c and the carry flag from a.
		{},

		//! 9A; SBC a,d: Subtracts d and the carry flag from a.
		{},

		//! 9B; SBC a,e: Subtracts e and the carry flag from a.
		{},

		//! 9C; SBC a,h: Subtracts h and the carry flag from a.
		{},

		//! 9D; SBC a,l: Subtracts l and the carry flag from a.
		{},

		//! 9E; SBC a,(hl): Subtracts (hl) and the carry flag from a.
		{},

		//! 9F; SBC a,a: Subtracts a and the carry flag from a.
		{},

		//! A0; AND b: Bitwise AND on a with b.
		[](CPU &, CPU::Registers &reg) { return AND8(reg, reg.a, reg.b); },

		//! A1; AND c: Bitwise AND on a with c.
		[](CPU &, CPU::Registers &reg) { return AND8(reg, reg.a, reg.c); },

		//! A2; AND d: Bitwise AND on a with d.
		[](CPU &, CPU::Registers &reg) { return AND8(reg, reg.a, reg.d); },

		//! A3; AND e: Bitwise AND on a with e.
		[](CPU &, CPU::Registers &reg) { return AND8(reg, reg.a, reg.e); },

		//! A4; AND h: Bitwise AND on a with h.
		[](CPU &, CPU::Registers &reg) { return AND8(reg, reg.a, reg.h); },

		//! A5; AND l: Bitwise AND on a with l.
		[](CPU &, CPU::Registers &reg) { return AND8(reg, reg.a, reg.l); },

		//! A6; AND (hl): Bitwise AND on a with (hl).
		[](CPU &cpu, CPU::Registers &reg) { return AND8(reg, reg.a, cpu.read(reg.hl)) + INDIRECTION_CYLCE_DURATION; },

		//! A7; AND a: Bitwise AND on a with a.
		[](CPU &, CPU::Registers &reg) { return AND8(reg, reg.a, reg.a); },

		//! A8; XOR b: Bitwise XOR on a with b.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.b); },

		//! A9; XOR c: Bitwise XOR on a with c.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.l); },

		//! AA; XOR d: Bitwise XOR on a with d.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.d); },

		//! AB; XOR e: Bitwise XOR on a with e.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.e); },

		//! AC; XOR h: Bitwise XOR on a with h.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.h); },

		//! AD; XOR l: Bitwise XOR on a with l.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.l); },

		//! AE; XOR (hl): Bitwise XOR on a with (hl).
		[](CPU &cpu, CPU::Registers &reg) { return XOR(reg, cpu.read(reg.hl)) + INDIRECTION_CYLCE_DURATION; },

		//! AF; XOR a: Bitwise XOR a with a
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.a); },

		//! B0; OR b: Bitwise OR on a with b.
		[](CPU &, CPU::Registers &reg) { return OR8(reg, reg.a, reg.b); },

		//! B1; OR c: Bitwise OR on a with c.
		[](CPU &, CPU::Registers &reg) { return OR8(reg, reg.a, reg.c); },

		//! B2; OR d: Bitwise OR on a with d.
		[](CPU &, CPU::Registers &reg) { return OR8(reg, reg.a, reg.d); },

		//! B3; OR e: Bitwise OR on a with e.
		[](CPU &, CPU::Registers &reg) { return OR8(reg, reg.a, reg.e); },

		//! B4; OR h: Bitwise OR on a with h.
		[](CPU &, CPU::Registers &reg) { return OR8(reg, reg.a, reg.h); },

		//! B5; OR l: Bitwise OR on a with l.
		[](CPU &, CPU::Registers &reg) { return OR8(reg, reg.a, reg.l); },

		//! B6; OR (hl): Bitwise OR on a with (hl).
		[](CPU &cpu, CPU::Registers &reg) { return OR8(reg, reg.a, cpu.read(reg.hl)) + INDIRECTION_CYLCE_DURATION; },

		//! B7; OR a: Bitwise OR on a with a.
		[](CPU &, CPU::Registers &reg) { return OR8(reg, reg.a, reg.a); },

		//! B8; CP b: Subtracts b from a and affects flags according to the result. a is not modified.
		{},

		//! B9; CP c: Subtracts c from a and affects flags according to the result. a is not modified.
		{},

		//! BA; CP d: Subtracts d from a and affects flags according to the result. a is not modified.
		{},

		//! BB; CP e: Subtracts e from a and affects flags according to the result. a is not modified.
		{},

		//! BC; CP h: Subtracts h from a and affects flags according to the result. a is not modified.
		{},

		//! BD; CP l: Subtracts l from a and affects flags according to the result. a is not modified.
		{},

		//! BE; CP (hl): Subtracts (hl) from a and affects flags according to the result. a is not modified.
		[](CPU &cpu, CPU::Registers &reg) { return CP(reg, cpu.read(reg.hl)) + INDIRECTION_CYLCE_DURATION; },

		//! BF; CP a: Subtracts a from a and affects flags according to the result. a is not modified.
		{},

		//! C0; RET nz: If condition cc is true, the top stack entry is popped into pc.
		[](CPU &cpu, CPU::Registers &reg) { return RET(cpu, reg, !reg.fz); },

		//! C1; POP bc: The memory location pointed to by sp is stored into c and sp is incremented. The memory location pointed to by sp is stored into b and sp is incremented again.
		[](CPU &cpu, CPU::Registers &reg){ return POP(cpu, reg, reg.bc); },

		//! C2; JP nz,**: If condition cc is true, ** is copied to pc.
		{},

		//! C3; JP **: ** is copied to pc.
		[](CPU &cpu, CPU::Registers &reg) { return JP(reg, true, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! C4; CALL nz,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		{},

		//! C5; PUSH bc: sp is decremented and b is stored into the memory location pointed to by sp. sp is decremented again and c is stored into the memory location pointed to by sp.
		[](CPU &cpu, CPU::Registers &reg){ return PUSH(cpu, reg, reg.bc); },

		//! C6; ADD a,*: Adds * to a.
		[](CPU &cpu, CPU::Registers &reg) { return ADD8(reg, reg.a, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! C7; RST 00h: The current pc value plus one is pushed onto the stack, then is loaded with 00h.
		{},

		//! C8; RET z: If condition cc is true, the top stack entry is popped into pc.
		[](CPU &cpu, CPU::Registers &reg) { return RET(cpu, reg, reg.fz); },

		//! C9; RET: The top stack entry is popped into pc.
		[](CPU &cpu, CPU::Registers &reg){ return POP(cpu, reg, reg.pc); },

		//! CA; JP z,**: If condition cc is true, ** is copied to pc.
		[](CPU &cpu, CPU::Registers &reg) { return JP(reg, reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! CB; Prefix for bit level instructions
		[](CPU &cpu, CPU::Registers &reg) {
			unsigned char opcode = cpu.read(reg.pc++);

			try {
				return Instructions::_bitLevelInstructions[opcode](cpu, reg) + FETCH_ARGUMENT8_CYLCE_DURATION;
			} catch (std::bad_function_call &) {
				throw CPU::InvalidOpcodeException(0xCB00U | opcode, reg.pc - 2);
			}
		},

		//! CC; CALL z,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		{},

		//! CD; CALL **: The current pc value plus three is pushed onto the stack, then is loaded with **.
		[](CPU &cpu, CPU::Registers &reg){ return CALL(cpu, reg, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! CE; ADC a,*: Adds * and the carry flag to a.
		{},

		//! CF; RST 08h: The current pc value plus one is pushed onto the stack, then is loaded with 08h.
		{},

		//! D0; RET nc: If condition cc is true, the top stack entry is popped into pc.
		{},

		//! D1; POP de: The memory location pointed to by sp is stored into e and sp is incremented. The memory location pointed to by sp is stored into d and sp is incremented again.
		[](CPU &cpu, CPU::Registers &reg) { return POP(cpu, reg, reg.de); },

		//! D2; JP nc,**: If condition cc is true, ** is copied to pc.
		{},

		//! D3; UNUSED
		{},

		//! D4; CALL nc,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		{},

		//! D5; PUSH de: sp is decremented and d is stored into the memory location pointed to by sp. sp is decremented again and e is stored into the memory location pointed to by sp.
		[](CPU &cpu, CPU::Registers &reg) { return PUSH(cpu, reg, reg.de); },

		//! D6; SUB *: Subtracts * from a.
		{},

		//! D7; RST 10h: The current pc value plus one is pushed onto the stack, then is loaded with 10h.
		{},

		//! D8; RET c: If condition cc is true, the top stack entry is popped into pc.
		{},

		//! D9; RETI
		{},

		//! DA; JP c,**: If condition cc is true, ** is copied to pc.
		{},

		//! DB; UNUSED
		{},

		//! DC; CALL c,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		{},

		//! DD; UNUSED
		{},

		//! DE; SBC a,*: Subtracts * and the carry flag from a.
		{},

		//! DF; RST 18h: The current pc value plus one is pushed onto the stack, then is loaded with 18h.
		{},

		//! E0; LD (FF00+*),a: Load a to the address $FF00+*
		[](CPU &cpu, CPU::Registers &reg){ return LD8toPTR(cpu, 0xFF00 + cpu.fetchArgument(), reg.a); },

		//! E1; POP hl: The memory location pointed to by sp is stored into l and sp is incremented. The memory location pointed to by sp is stored into h and sp is incremented again.
		[](CPU &cpu, CPU::Registers &reg) { return POP(cpu, reg, reg.hl); },

		//! E2; LD (FF00+c),a: Load a to the address $FF00+c
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, reg.c + 0xFF00, reg.a); },

		//! E3; UNUSED
		{},

		//! E4; UNUSED
		{},

		//! E5; PUSH hl: sp is decremented and h is stored into the memory location pointed to by sp. sp is decremented again and l is stored into the memory location pointed to by sp.
		[](CPU &cpu, CPU::Registers &reg) { return PUSH(cpu, reg, reg.hl); },

		//! E6; AND *: Bitwise AND on a with *.
		[](CPU &cpu, CPU::Registers &reg) { return AND8(reg, reg.a, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! E7; RST 20h: The current pc value plus one is pushed onto the stack, then is loaded with 20h.
		{},

		//! E8; ADD SP,**: Add ** to sp.
		{},

		//! E9; JP (hl): Loads the value of hl into pc.
		{},

		//! EA; LD (**),a: Load a into the address pointed to by **
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, cpu.fetchArgument16(), reg.a) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! EB; UNUSED
		{},

		//! EC; UNUSED
		{},

		//! ED; UNUSED
		{},

		//! EE; XOR *: Bitwise XOR on a with *.
		[](CPU &cpu, CPU::Registers &reg) { return XOR(reg, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! EF; RST 28h: The current pc value plus one is pushed onto the stack, then is loaded with 28h.
		{},

		//! F0; LD a,(FF00+*): Load the value at address $FF00+* to a
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, cpu.fetchArgument() + 0xFF00) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! F1; POP af: The memory location pointed to by sp is stored into f and sp is incremented. The memory location pointed to by sp is stored into a and sp is incremented again.
		[](CPU &cpu, CPU::Registers &reg) { return POP(cpu, reg, reg.af); },

		//! F2; LD a,(FF00+c): Load the value at address $FF00+c to a.
		{},

		//! F3; DI: Resets both interrupt flip-flops, thus prenting maskable interrupts from triggering.
		[](CPU &cpu, CPU::Registers &) { return cpu.setInterruptMaster(false), LD_CYCLE_DURATION; },

		//! F4; UNUSED
		{},

		//! F5; PUSH af: sp is decremented and a is stored into the memory location pointed to by sp. sp is decremented again and f is stored into the memory location pointed to by sp.
		[](CPU &cpu, CPU::Registers &reg) { return PUSH(cpu, reg, reg.af); },

		//! F6; OR *: Bitwise OR on a with *.
		{},

		//! F7; RST 30h: The current pc value plus one is pushed onto the stack, then is loaded with 30h.
		{},

		//! F8; LD hl,sp+**: Load sp+** to hl.
		{},

		//! F9; LD sp,hl: Loads the value of hl into sp.
		[](CPU &, CPU::Registers &reg) { return LD16(reg.sp, reg.hl); },

		//! FA; LD a,(**): Load the value pointed to by address ** to a
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! FB; EI: Sets both interrupt flip-flops, thus allowing maskable interrupts to occur. An interrupt will not occur until after the immediatedly following instruction.
		[](CPU &cpu, CPU::Registers &) { return cpu.setInterruptMaster(true), LD_CYCLE_DURATION; },

		//! FC; UNUSED
		{},

		//! FD; UNUSED
		{},

		//! FE; CP *: Subtracts * from a and affects flags according to the result. a is not modified.
		[](CPU &cpu, CPU::Registers &reg) { return CP(reg, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! FF; RST 38h: The current pc value plus one is pushed onto the stack, then is loaded with 38h.
		{}

	};

	void setFlags(CPU::Registers &reg, FlagValue z, FlagValue n, FlagValue h, FlagValue c)
	{
		reg._ = 0;
		if (z != UNCHANGED)
			reg.fz = z;
		if (n != UNCHANGED)
			reg.fn = n;
		if (h != UNCHANGED)
			reg.fh = h;
		if (c != UNCHANGED)
			reg.fc = c;
	}

	unsigned char CALL(CPU &cpu, CPU::Registers &reg, unsigned short address)
	{
		PUSH(cpu, reg, reg.pc);
		JP(reg, true, address);
		return PUSH_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}

	unsigned char PUSH(CPU &cpu, CPU::Registers &reg, unsigned short value)
	{
		cpu.write(--reg.sp, value >> 8U);
		cpu.write(--reg.sp, value);
		return PUSH_CYCLE_DURATION;
	}

	unsigned char POP(CPU &cpu, CPU::Registers &reg, unsigned short &value)
	{
		unsigned char temp = cpu.read(reg.sp++);

		value = (cpu.read(reg.sp++) << 8U) | temp;
		return PUSH_CYCLE_DURATION;
	}

	unsigned char RET(CPU &cpu, CPU::Registers &reg, bool cond)
	{
		if (cond)
			return POP(cpu, reg, reg.pc) + COMPLEX_BIT_OPERATION_CYCLE_DURATION;
		return COMPLEX_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char JR(CPU::Registers &reg, bool cond, char off)
	{
		if (!cond)
			return BASIC_BIT_OPERATION_CYCLE_DURATION;
		reg.pc += off;
		return BASIC_BIT_OPERATION_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}

	unsigned char JP(CPU::Registers &reg, bool cond, unsigned short address)
	{
		if (!cond)
			return BASIC_BIT_OPERATION_CYCLE_DURATION;
		reg.pc = address;
		return BASIC_BIT_OPERATION_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}

	unsigned char BIT(CPU::Registers &reg, unsigned char value, unsigned char bit)
	{
		setFlags(reg, ((1U << bit) & value) == 0 ? SET : UNSET, UNSET, SET, UNCHANGED);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char XOR(CPU::Registers &reg, unsigned char value)
	{
		reg.a ^= value;
		setFlags(reg, reg.a == 0 ? SET : UNSET, UNSET, UNSET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char LD8(unsigned char &register1, unsigned char value)
	{
		register1 = value;
		return LD_CYCLE_DURATION;
	}

	unsigned char LD16(unsigned short &double_register, unsigned short value)
	{
		double_register = value;
		return LD_CYCLE_DURATION;
	}

	unsigned char LD8toPTR(CPU &cpu, unsigned short address, unsigned char value)
	{
		cpu.write(address, value);
		return LD_CYCLE_DURATION + INDIRECTION_CYLCE_DURATION;
	}

	unsigned char LD8fromPTR(CPU &cpu, unsigned char &value, unsigned short address)
	{
		value = cpu.read(address);
		return LD_CYCLE_DURATION + INDIRECTION_CYLCE_DURATION;
	}

	unsigned char LD16toPTR(CPU &cpu, unsigned short address, unsigned short value)
	{
		cpu.write(address, value & 0x00FFU);
		cpu.write(address + 1, value >> 8U);
		return LD_CYCLE_DURATION * 2 + INDIRECTION_CYLCE_DURATION;
	}

	unsigned char LD16fromPTR(CPU &cpu, unsigned short &value, unsigned short address)
	{
		value = cpu.read(address);
		value += cpu.read(address + 1) << 8U;
		return LD_CYCLE_DURATION * 2 + INDIRECTION_CYLCE_DURATION;
	}

	unsigned char RL(CPU::Registers &reg, unsigned char &value)
	{
		unsigned char newValue = (value << 1U) | reg.fc;

		setFlags(reg, newValue == 0 ? SET : UNSET, UNSET, UNSET, value & (1U << 7U) ? SET : UNSET);
		value = newValue;
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char AND8(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		value1 &= value2;
		setFlags(reg, value1 == 0 ? SET : UNSET, UNSET, SET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char OR8(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		value1 |= value2;
		setFlags(reg, value1 == 0 ? SET : UNSET, UNSET, UNSET, UNSET);
		return BASIC_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char ADD8(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		bool halfCarry = (((value1 & 0xFU) + (value2 & 0xFU)) & 0x10U) == 0x10U;

		value1 += value2;
		setFlags(
			reg,
			value1 == 0 ? SET : UNSET,
			UNSET,
			halfCarry ? SET : UNSET,
			value1 + value2 > 0xFF ? SET : UNSET
		);
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}

	unsigned char SUB8(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		bool halfCarry = (((value1 & 0xFU) - (value2 & 0xFU)) & 0x8U) == 0x8U;

		value1 -= value2;
		setFlags(
			reg,
			value1 == 0 ? SET : UNSET,
			UNSET,
			halfCarry ? SET : UNSET,
			value1 < value2 ? SET : UNSET
		);
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}

	unsigned char ADD16(CPU::Registers &reg, unsigned short &value1, unsigned short value2)
	{
		bool halfCarry = (((value1 & 0xFFU) + (value2 & 0xFFU)) & 0x100U) == 0x100U;

		value1 += value2;
		setFlags(
			reg,
			UNCHANGED,
			UNSET,
			halfCarry ? SET : UNSET,
			value1 + value2 > 0xFFFF ? SET : UNSET
		);
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}

	unsigned char SUB16(CPU::Registers &reg, unsigned short &value1, unsigned short value2)
	{
		bool halfCarry = (((value1 & 0xFFU) - (value2 & 0xFFU)) & 0x80U) == 0x80U;

		value1 -= value2;
		setFlags(
			reg,
			UNCHANGED,
			UNSET,
			halfCarry ? SET : UNSET,
			value1 < value2 ? SET : UNSET
		);
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}

	unsigned char INC8(CPU::Registers &reg, unsigned char &value)
	{
		bool halfCarry = (((value & 0xf) + 1) & 0x10) == 0x10;

		value++;
		setFlags(
			reg,
			value == 0 ? SET : UNSET,
			UNSET,
			halfCarry ? SET : UNSET,
			UNCHANGED
		);
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}

	unsigned char DEC8(CPU::Registers &reg, unsigned char &value)
	{
		bool halfCarry = (((value & 0xf) - 1) & 0x8) == 0x8;

		value--;
		setFlags(
			reg,
			value == 0 ? SET : UNSET,
			UNSET,
			halfCarry ? SET : UNSET,
			UNCHANGED
		);
		return ARITHMETIC_OPERATION_CYCLE_DURATION;
	}

	unsigned char INC16(unsigned short &value)
	{
		value++;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}

	unsigned char DEC16(unsigned short &value)
	{
		value--;
		return ARITHMETIC_OPERATION_CYCLE_DURATION * 2;
	}

	unsigned char INCPTR(CPU &cpu, CPU::Registers &reg, unsigned short &address)
	{
		auto tmp = cpu.read(address);
		auto rt_value = INC8(reg, tmp) + INDIRECTION_CYLCE_DURATION;

		cpu.write(address, tmp);
		return rt_value;
	}

	unsigned char DECPTR(CPU &cpu, CPU::Registers &reg, unsigned short &address)
	{
		auto tmp = cpu.read(address);
		auto rt_value = DEC8(reg, tmp) + INDIRECTION_CYLCE_DURATION;

		cpu.write(address, tmp);
		return rt_value;
	}

	unsigned char CP(CPU::Registers &reg, unsigned char value)
	{
		unsigned char buf = reg.a;

		return SUB8(reg, buf, value);
	}

	unsigned char RES(unsigned char &val, unsigned char bit)
	{
		val &= ~(1U << bit);
		return 4;
	}
}