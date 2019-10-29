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
}