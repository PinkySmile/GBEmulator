/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** BitInstructions.cpp
*/

#include "CPUInstructions.hpp"

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

		//! 40; BIT 0,b
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.b, 0); },

		//! 41; BIT 0,c
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.c, 0); },

		//! 42; BIT 0,d
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.d, 0); },

		//! 43; BIT 0,e
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.e, 0); },

		//! 44; BIT 0,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 0); },

		//! 45; BIT 0,l
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.l, 0); },

		//! 46; BIT 0,(hl)
		[](CPU &cpu, CPU::Registers &reg){ return BIT(reg, cpu.read(reg.hl), 0) + INDIRECTION_CYLCE_DURATION; },

		//! 47; BIT 0,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 0); },

		//! 48; BIT 1,b
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.b, 1); },

		//! 49; BIT 1,c
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.c, 1); },

		//! 4A; BIT 1,d
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.d, 1); },

		//! 4B; BIT 1,e
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.e, 1); },

		//! 4C; BIT 1,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 1); },

		//! 4D; BIT 1,l
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.l, 1); },

		//! 4E; BIT 1,(hl)
		[](CPU &cpu, CPU::Registers &reg){ return BIT(reg, cpu.read(reg.hl), 1) + INDIRECTION_CYLCE_DURATION; },

		//! 4F; BIT 1,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 1); },

		//! 50; BIT 2,b
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.b, 2); },

		//! 51; BIT 2,c
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.c, 2); },

		//! 52; BIT 2,d
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.d, 2); },

		//! 53; BIT 2,e
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.e, 2); },

		//! 54; BIT 2,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 2); },

		//! 55; BIT 2,l
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.l, 2); },

		//! 56; BIT 2,(hl)
		[](CPU &cpu, CPU::Registers &reg){ return BIT(reg, cpu.read(reg.hl), 2) + INDIRECTION_CYLCE_DURATION; },

		//! 57; BIT 2,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 2); },

		//! 58; BIT 3,b
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.b, 3); },

		//! 59; BIT 3,c
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.c, 3); },

		//! 5A; BIT 3,d
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.d, 3); },

		//! 5B; BIT 3,e
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.e, 3); },

		//! 5C; BIT 3,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 3); },

		//! 5D; BIT 3,l
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.l, 3); },

		//! 5E; BIT 3,(hl)
		[](CPU &cpu, CPU::Registers &reg){ return BIT(reg, cpu.read(reg.hl), 3) + INDIRECTION_CYLCE_DURATION; },

		//! 5F; BIT 3,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 3); },

		//! 60; BIT 4,b
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.b, 4); },

		//! 61; BIT 4,c
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.c, 4); },

		//! 62; BIT 4,d
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.d, 4); },

		//! 63; BIT 4,e
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.e, 4); },

		//! 64; BIT 4,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 4); },

		//! 65; BIT 4,l
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.l, 4); },

		//! 66; BIT 4,(hl)
		[](CPU &cpu, CPU::Registers &reg){ return BIT(reg, cpu.read(reg.hl), 4) + INDIRECTION_CYLCE_DURATION; },

		//! 67; BIT 4,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 4); },

		//! 68; BIT 5,b
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.b, 5); },

		//! 69; BIT 5,c
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.c, 5); },

		//! 6A; BIT 5,d
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.d, 5); },

		//! 6B; BIT 5,e
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.e, 5); },

		//! 6C; BIT 5,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 5); },

		//! 6D; BIT 5,l
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.l, 5); },

		//! 6E; BIT 5,(hl)
		[](CPU &cpu, CPU::Registers &reg){ return BIT(reg, cpu.read(reg.hl), 5) + INDIRECTION_CYLCE_DURATION; },

		//! 6F; BIT 5,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 5); },

		//! 70; BIT 6,b
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.b, 6); },

		//! 71; BIT 6,c
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.c, 6); },

		//! 72; BIT 6,d
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.d, 6); },

		//! 73; BIT 6,e
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.e, 6); },

		//! 74; BIT 6,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 6); },

		//! 75; BIT 6,l
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.l, 6); },

		//! 76; BIT 6,(hl)
		[](CPU &cpu, CPU::Registers &reg){ return BIT(reg, cpu.read(reg.hl), 6) + INDIRECTION_CYLCE_DURATION; },

		//! 77; BIT 6,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 6); },

		//! 78; BIT 7,b
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.b, 7); },

		//! 79; BIT 7,c
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.c, 7); },

		//! 7A; BIT 7,d
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.d, 7); },

		//! 7B; BIT 7,e
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.e, 7); },

		//! 7C; BIT 7,h
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 7); },

		//! 7D; BIT 7,l
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.l, 7); },

		//! 7E; BIT 7,(hl)
		[](CPU &cpu, CPU::Registers &reg){ return BIT(reg, cpu.read(reg.hl), 7) + INDIRECTION_CYLCE_DURATION; },

		//! 7F; BIT 7,a
		[](CPU &, CPU::Registers &reg){ return BIT(reg, reg.a, 7); },

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
//! 00; RLC b: The contents of b are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

//! 01; RLC c: The contents of c are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

//! 02; RLC d: The contents of d are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

//! 03; RLC e: The contents of e are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

//! 04; RLC h: The contents of h are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

//! 05; RLC l: The contents of l are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

//! 06; RLC (hl): The contents of (hl) are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

//! 07; RLC a: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

//! 08; RRC b: The contents of b are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

//! 09; RRC c: The contents of c are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

//! 0A; RRC d: The contents of d are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

//! 0B; RRC e: The contents of e are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

//! 0C; RRC h: The contents of h are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

//! 0D; RRC l: The contents of l are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

//! 0E; RRC (hl): The contents of (hl) are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

//! 0F; RRC a: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

//! 10; RL b: The contents of b are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

//! 11; RL c: The contents of c are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

//! 12; RL d: The contents of d are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

//! 13; RL e: The contents of e are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

//! 14; RL h: The contents of h are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

//! 15; RL l: The contents of l are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

//! 16; RL (hl): The contents of (hl) are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

//! 17; RL a: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

//! 18; RR b: The contents of b are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

//! 19; RR c: The contents of c are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

//! 1A; RR d: The contents of d are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

//! 1B; RR e: The contents of e are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

//! 1C; RR h: The contents of h are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

//! 1D; RR l: The contents of l are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

//! 1E; RR (hl): The contents of (hl) are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

//! 1F; RR a: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

//! 20; SLA b: The contents of b are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.

//! 21; SLA c: The contents of c are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.

//! 22; SLA d: The contents of d are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.

//! 23; SLA e: The contents of e are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.

//! 24; SLA h: The contents of h are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.

//! 25; SLA l: The contents of l are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.

//! 26; SLA (hl): The contents of (hl) are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.

//! 27; SLA a: The contents of a are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.

//! 28; SRA b: The contents of b are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.

//! 29; SRA c: The contents of c are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.

//! 2A; SRA d: The contents of d are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.

//! 2B; SRA e: The contents of e are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.

//! 2C; SRA h: The contents of h are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.

//! 2D; SRA l: The contents of l are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.

//! 2E; SRA (hl): The contents of (hl) are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.

//! 2F; SRA a: The contents of a are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.

//! 30; SLL b: The contents of b are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.

//! 31; SLL c: The contents of c are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.

//! 32; SLL d: The contents of d are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.

//! 33; SLL e: The contents of e are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.

//! 34; SLL h: The contents of h are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.

//! 35; SLL l: The contents of l are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.

//! 36; SLL (hl): The contents of (hl) are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.

//! 37; SLL a: The contents of a are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.

//! 38; SRL b: The contents of b are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.

//! 39; SRL c: The contents of c are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.

//! 3A; SRL d: The contents of d are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.

//! 3B; SRL e: The contents of e are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.

//! 3C; SRL h: The contents of h are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.

//! 3D; SRL l: The contents of l are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.

//! 3E; SRL (hl): The contents of (hl) are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.

//! 3F; SRL a: The contents of a are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.

//! 40; BIT 0,b: Tests bit 0 of b.

//! 41; BIT 0,c: Tests bit 0 of c.

//! 42; BIT 0,d: Tests bit 0 of d.

//! 43; BIT 0,e: Tests bit 0 of e.

//! 44; BIT 0,h: Tests bit 0 of h.

//! 45; BIT 0,l: Tests bit 0 of l.

//! 46; BIT 0,(hl): Tests bit 0 of (hl).

//! 47; BIT 0,a: Tests bit 0 of a.

//! 48; BIT 1,b: Tests bit 1 of b.

//! 49; BIT 1,c: Tests bit 1 of c.

//! 4A; BIT 1,d: Tests bit 1 of d.

//! 4B; BIT 1,e: Tests bit 1 of e.

//! 4C; BIT 1,h: Tests bit 1 of h.

//! 4D; BIT 1,l: Tests bit 1 of l.

//! 4E; BIT 1,(hl): Tests bit 1 of (hl).

//! 4F; BIT 1,a: Tests bit 1 of a.

//! 50; BIT 2,b: Tests bit 2 of b.

//! 51; BIT 2,c: Tests bit 2 of c.

//! 52; BIT 2,d: Tests bit 2 of d.

//! 53; BIT 2,e: Tests bit 2 of e.

//! 54; BIT 2,h: Tests bit 2 of h.

//! 55; BIT 2,l: Tests bit 2 of l.

//! 56; BIT 2,(hl): Tests bit 2 of (hl).

//! 57; BIT 2,a: Tests bit 2 of a.

//! 58; BIT 3,b: Tests bit 3 of b.

//! 59; BIT 3,c: Tests bit 3 of c.

//! 5A; BIT 3,d: Tests bit 3 of d.

//! 5B; BIT 3,e: Tests bit 3 of e.

//! 5C; BIT 3,h: Tests bit 3 of h.

//! 5D; BIT 3,l: Tests bit 3 of l.

//! 5E; BIT 3,(hl): Tests bit 3 of (hl).

//! 5F; BIT 3,a: Tests bit 3 of a.

//! 60; BIT 4,b: Tests bit 4 of b.

//! 61; BIT 4,c: Tests bit 4 of c.

//! 62; BIT 4,d: Tests bit 4 of d.

//! 63; BIT 4,e: Tests bit 4 of e.

//! 64; BIT 4,h: Tests bit 4 of h.

//! 65; BIT 4,l: Tests bit 4 of l.

//! 66; BIT 4,(hl): Tests bit 4 of (hl).

//! 67; BIT 4,a: Tests bit 4 of a.

//! 68; BIT 5,b: Tests bit 5 of b.

//! 69; BIT 5,c: Tests bit 5 of c.

//! 6A; BIT 5,d: Tests bit 5 of d.

//! 6B; BIT 5,e: Tests bit 5 of e.

//! 6C; BIT 5,h: Tests bit 5 of h.

//! 6D; BIT 5,l: Tests bit 5 of l.

//! 6E; BIT 5,(hl): Tests bit 5 of (hl).

//! 6F; BIT 5,a: Tests bit 5 of a.

//! 70; BIT 6,b: Tests bit 6 of b.

//! 71; BIT 6,c: Tests bit 6 of c.

//! 72; BIT 6,d: Tests bit 6 of d.

//! 73; BIT 6,e: Tests bit 6 of e.

//! 74; BIT 6,h: Tests bit 6 of h.

//! 75; BIT 6,l: Tests bit 6 of l.

//! 76; BIT 6,(hl): Tests bit 6 of (hl).

//! 77; BIT 6,a: Tests bit 6 of a.

//! 78; BIT 7,b: Tests bit 7 of b.

//! 79; BIT 7,c: Tests bit 7 of c.

//! 7A; BIT 7,d: Tests bit 7 of d.

//! 7B; BIT 7,e: Tests bit 7 of e.

//! 7C; BIT 7,h: Tests bit 7 of h.

//! 7D; BIT 7,l: Tests bit 7 of l.

//! 7E; BIT 7,(hl): Tests bit 7 of (hl).

//! 7F; BIT 7,a: Tests bit 7 of a.

//! 80; RES 0,b: Resets bit 0 of b.

//! 81; RES 0,c: Resets bit 0 of c.

//! 82; RES 0,d: Resets bit 0 of d.

//! 83; RES 0,e: Resets bit 0 of e.

//! 84; RES 0,h: Resets bit 0 of h.

//! 85; RES 0,l: Resets bit 0 of l.

//! 86; RES 0,(hl): Resets bit 0 of (hl).

//! 87; RES 0,a: Resets bit 0 of a.

//! 88; RES 1,b: Resets bit 1 of b.

//! 89; RES 1,c: Resets bit 1 of c.

//! 8A; RES 1,d: Resets bit 1 of d.

//! 8B; RES 1,e: Resets bit 1 of e.

//! 8C; RES 1,h: Resets bit 1 of h.

//! 8D; RES 1,l: Resets bit 1 of l.

//! 8E; RES 1,(hl): Resets bit 1 of (hl).

//! 8F; RES 1,a: Resets bit 1 of a.

//! 90; RES 2,b: Resets bit 2 of b.

//! 91; RES 2,c: Resets bit 2 of c.

//! 92; RES 2,d: Resets bit 2 of d.

//! 93; RES 2,e: Resets bit 2 of e.

//! 94; RES 2,h: Resets bit 2 of h.

//! 95; RES 2,l: Resets bit 2 of l.

//! 96; RES 2,(hl): Resets bit 2 of (hl).

//! 97; RES 2,a: Resets bit 2 of a.

//! 98; RES 3,b: Resets bit 3 of b.

//! 99; RES 3,c: Resets bit 3 of c.

//! 9A; RES 3,d: Resets bit 3 of d.

//! 9B; RES 3,e: Resets bit 3 of e.

//! 9C; RES 3,h: Resets bit 3 of h.

//! 9D; RES 3,l: Resets bit 3 of l.

//! 9E; RES 3,(hl): Resets bit 3 of (hl).

//! 9F; RES 3,a: Resets bit 3 of a.

//! A0; RES 4,b: Resets bit 4 of b.

//! A1; RES 4,c: Resets bit 4 of c.

//! A2; RES 4,d: Resets bit 4 of d.

//! A3; RES 4,e: Resets bit 4 of e.

//! A4; RES 4,h: Resets bit 4 of h.

//! A5; RES 4,l: Resets bit 4 of l.

//! A6; RES 4,(hl): Resets bit 4 of (hl).

//! A7; RES 4,a: Resets bit 4 of a.

//! A8; RES 5,b: Resets bit 5 of b.

//! A9; RES 5,c: Resets bit 5 of c.

//! AA; RES 5,d: Resets bit 5 of d.

//! AB; RES 5,e: Resets bit 5 of e.

//! AC; RES 5,h: Resets bit 5 of h.

//! AD; RES 5,l: Resets bit 5 of l.

//! AE; RES 5,(hl): Resets bit 5 of (hl).

//! AF; RES 5,a: Resets bit 5 of a.

//! B0; RES 6,b: Resets bit 6 of b.

//! B1; RES 6,c: Resets bit 6 of c.

//! B2; RES 6,d: Resets bit 6 of d.

//! B3; RES 6,e: Resets bit 6 of e.

//! B4; RES 6,h: Resets bit 6 of h.

//! B5; RES 6,l: Resets bit 6 of l.

//! B6; RES 6,(hl): Resets bit 6 of (hl).

//! B7; RES 6,a: Resets bit 6 of a.

//! B8; RES 7,b: Resets bit 7 of b.

//! B9; RES 7,c: Resets bit 7 of c.

//! BA; RES 7,d: Resets bit 7 of d.

//! BB; RES 7,e: Resets bit 7 of e.

//! BC; RES 7,h: Resets bit 7 of h.

//! BD; RES 7,l: Resets bit 7 of l.

//! BE; RES 7,(hl): Resets bit 7 of (hl).

//! BF; RES 7,a: Resets bit 7 of a.

//! C0; SET 0,b: Sets bit 0 of b.

//! C1; SET 0,c: Sets bit 0 of c.

//! C2; SET 0,d: Sets bit 0 of d.

//! C3; SET 0,e: Sets bit 0 of e.

//! C4; SET 0,h: Sets bit 0 of h.

//! C5; SET 0,l: Sets bit 0 of l.

//! C6; SET 0,(hl): Sets bit 0 of (hl).

//! C7; SET 0,a: Sets bit 0 of a.

//! C8; SET 1,b: Sets bit 1 of b.

//! C9; SET 1,c: Sets bit 1 of c.

//! CA; SET 1,d: Sets bit 1 of d.

//! CB; SET 1,e: Sets bit 1 of e.

//! CC; SET 1,h: Sets bit 1 of h.

//! CD; SET 1,l: Sets bit 1 of l.

//! CE; SET 1,(hl): Sets bit 1 of (hl).

//! CF; SET 1,a: Sets bit 1 of a.

//! D0; SET 2,b: Sets bit 2 of b.

//! D1; SET 2,c: Sets bit 2 of c.

//! D2; SET 2,d: Sets bit 2 of d.

//! D3; SET 2,e: Sets bit 2 of e.

//! D4; SET 2,h: Sets bit 2 of h.

//! D5; SET 2,l: Sets bit 2 of l.

//! D6; SET 2,(hl): Sets bit 2 of (hl).

//! D7; SET 2,a: Sets bit 2 of a.

//! D8; SET 3,b: Sets bit 3 of b.

//! D9; SET 3,c: Sets bit 3 of c.

//! DA; SET 3,d: Sets bit 3 of d.

//! DB; SET 3,e: Sets bit 3 of e.

//! DC; SET 3,h: Sets bit 3 of h.

//! DD; SET 3,l: Sets bit 3 of l.

//! DE; SET 3,(hl): Sets bit 3 of (hl).

//! DF; SET 3,a: Sets bit 3 of a.

//! E0; SET 4,b: Sets bit 4 of b.

//! E1; SET 4,c: Sets bit 4 of c.

//! E2; SET 4,d: Sets bit 4 of d.

//! E3; SET 4,e: Sets bit 4 of e.

//! E4; SET 4,h: Sets bit 4 of h.

//! E5; SET 4,l: Sets bit 4 of l.

//! E6; SET 4,(hl): Sets bit 4 of (hl).

//! E7; SET 4,a: Sets bit 4 of a.

//! E8; SET 5,b: Sets bit 5 of b.

//! E9; SET 5,c: Sets bit 5 of c.

//! EA; SET 5,d: Sets bit 5 of d.

//! EB; SET 5,e: Sets bit 5 of e.

//! EC; SET 5,h: Sets bit 5 of h.

//! ED; SET 5,l: Sets bit 5 of l.

//! EE; SET 5,(hl): Sets bit 5 of (hl).

//! EF; SET 5,a: Sets bit 5 of a.

//! F0; SET 6,b: Sets bit 6 of b.

//! F1; SET 6,c: Sets bit 6 of c.

//! F2; SET 6,d: Sets bit 6 of d.

//! F3; SET 6,e: Sets bit 6 of e.

//! F4; SET 6,h: Sets bit 6 of h.

//! F5; SET 6,l: Sets bit 6 of l.

//! F6; SET 6,(hl): Sets bit 6 of (hl).

//! F7; SET 6,a: Sets bit 6 of a.

//! F8; SET 7,b: Sets bit 7 of b.

//! F9; SET 7,c: Sets bit 7 of c.

//! FA; SET 7,d: Sets bit 7 of d.

//! FB; SET 7,e: Sets bit 7 of e.

//! FC; SET 7,h: Sets bit 7 of h.

//! FD; SET 7,l: Sets bit 7 of l.

//! FE; SET 7,(hl): Sets bit 7 of (hl).

//! FF; SET 7,a: Sets bit 7 of a.
	const std::function<std::string (const CPU &, unsigned short)> _bitLevelInstructionsString[256] = {
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		[](const CPU &, unsigned short){ return "RL c"; },
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		[](const CPU &, unsigned short){ return "BIT 0,b"; },
		[](const CPU &, unsigned short){ return "BIT 0,c"; },
		[](const CPU &, unsigned short){ return "BIT 0,d"; },
		[](const CPU &, unsigned short){ return "BIT 0,e"; },
		[](const CPU &, unsigned short){ return "BIT 0,h"; },
		[](const CPU &, unsigned short){ return "BIT 0,l"; },
		[](const CPU &, unsigned short){ return "BIT 0,(hl)"; },
		[](const CPU &, unsigned short){ return "BIT 0,a"; },
		[](const CPU &, unsigned short){ return "BIT 1,b"; },
		[](const CPU &, unsigned short){ return "BIT 1,c"; },
		[](const CPU &, unsigned short){ return "BIT 1,d"; },
		[](const CPU &, unsigned short){ return "BIT 1,e"; },
		[](const CPU &, unsigned short){ return "BIT 1,h"; },
		[](const CPU &, unsigned short){ return "BIT 1,l"; },
		[](const CPU &, unsigned short){ return "BIT 1,(hl)"; },
		[](const CPU &, unsigned short){ return "BIT 1,a"; },
		[](const CPU &, unsigned short){ return "BIT 2,b"; },
		[](const CPU &, unsigned short){ return "BIT 2,c"; },
		[](const CPU &, unsigned short){ return "BIT 2,d"; },
		[](const CPU &, unsigned short){ return "BIT 2,e"; },
		[](const CPU &, unsigned short){ return "BIT 2,h"; },
		[](const CPU &, unsigned short){ return "BIT 2,l"; },
		[](const CPU &, unsigned short){ return "BIT 2,(hl)"; },
		[](const CPU &, unsigned short){ return "BIT 2,a"; },
		[](const CPU &, unsigned short){ return "BIT 3,b"; },
		[](const CPU &, unsigned short){ return "BIT 3,c"; },
		[](const CPU &, unsigned short){ return "BIT 3,d"; },
		[](const CPU &, unsigned short){ return "BIT 3,e"; },
		[](const CPU &, unsigned short){ return "BIT 3,h"; },
		[](const CPU &, unsigned short){ return "BIT 3,l"; },
		[](const CPU &, unsigned short){ return "BIT 3,(hl)"; },
		[](const CPU &, unsigned short){ return "BIT 3,a"; },
		[](const CPU &, unsigned short){ return "BIT 4,b"; },
		[](const CPU &, unsigned short){ return "BIT 4,c"; },
		[](const CPU &, unsigned short){ return "BIT 4,d"; },
		[](const CPU &, unsigned short){ return "BIT 4,e"; },
		[](const CPU &, unsigned short){ return "BIT 4,h"; },
		[](const CPU &, unsigned short){ return "BIT 4,l"; },
		[](const CPU &, unsigned short){ return "BIT 4,(hl)"; },
		[](const CPU &, unsigned short){ return "BIT 4,a"; },
		[](const CPU &, unsigned short){ return "BIT 5,b"; },
		[](const CPU &, unsigned short){ return "BIT 5,c"; },
		[](const CPU &, unsigned short){ return "BIT 5,d"; },
		[](const CPU &, unsigned short){ return "BIT 5,e"; },
		[](const CPU &, unsigned short){ return "BIT 5,h"; },
		[](const CPU &, unsigned short){ return "BIT 5,l"; },
		[](const CPU &, unsigned short){ return "BIT 5,(hl)"; },
		[](const CPU &, unsigned short){ return "BIT 5,a"; },
		[](const CPU &, unsigned short){ return "BIT 6,b"; },
		[](const CPU &, unsigned short){ return "BIT 6,c"; },
		[](const CPU &, unsigned short){ return "BIT 6,d"; },
		[](const CPU &, unsigned short){ return "BIT 6,e"; },
		[](const CPU &, unsigned short){ return "BIT 6,h"; },
		[](const CPU &, unsigned short){ return "BIT 6,l"; },
		[](const CPU &, unsigned short){ return "BIT 6,(hl)"; },
		[](const CPU &, unsigned short){ return "BIT 6,a"; },
		[](const CPU &, unsigned short){ return "BIT 7,b"; },
		[](const CPU &, unsigned short){ return "BIT 7,c"; },
		[](const CPU &, unsigned short){ return "BIT 7,d"; },
		[](const CPU &, unsigned short){ return "BIT 7,e"; },
		[](const CPU &, unsigned short){ return "BIT 7,h"; },
		[](const CPU &, unsigned short){ return "BIT 7,l"; },
		[](const CPU &, unsigned short){ return "BIT 7,(hl)"; },
		[](const CPU &, unsigned short){ return "BIT 7,a"; },
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		[](const CPU &, unsigned short) { return "RES a"; },
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};
}