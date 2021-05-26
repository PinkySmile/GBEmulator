/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** BitInstructions.cpp
*/

#include "CPUInstructions.hpp"

namespace GBEmulator::Instructions
{
	unsigned executeBitInstruction(unsigned char opcode, CPU &cpu, CPU::Registers &reg)
	{
		switch (opcode) {
		//! 00; RLC b: The contents of b are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x00:
			return RLC(reg, reg.b);

		//! 01; RLC c: The contents of c are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x01:
			return RLC(reg, reg.c);

		//! 02; RLC d: The contents of d are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x02:
			return RLC(reg, reg.d);

		//! 03; RLC e: The contents of e are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x03:
			return RLC(reg, reg.e);

		//! 04; RLC h: The contents of h are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x04:
			return RLC(reg, reg.h);

		//! 05; RLC l: The contents of l are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x05:
			return RLC(reg, reg.l);

		//! 06; RLC (hl): The contents of (hl) are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x06:
			return executeOnPtr(cpu, reg.hl, RLC, reg);

		//! 07; RLC a: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x07:
			return RLC(reg, reg.a);

		//! 08; RRC b: The contents of b are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x08:
			return RRC(reg, reg.b);

		//! 09; RRC c: The contents of c are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x09:
			return RRC(reg, reg.c);

		//! 0A; RRC d: The contents of d are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x0A:
			return RRC(reg, reg.d);

		//! 0B; RRC e: The contents of e are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x0B:
			return RRC(reg, reg.e);

		//! 0C; RRC h: The contents of h are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x0C:
			return RRC(reg, reg.h);

		//! 0D; RRC l: The contents of l are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x0D:
			return RRC(reg, reg.l);

		//! 0E; RRC (hl): The contents of (hl) are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x0E:
			return executeOnPtr(cpu, reg.hl, RRC, reg);

		//! 0F; RRC a: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x0F:
			return RRC(reg, reg.a);

		//! 10; RL b: The contents of b are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x10:
			return RL(reg, reg.b);

		//! 11; RL c: The contents of c are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x11:
			return RL(reg, reg.c);

		//! 12; RL d: The contents of d are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x12:
			return RL(reg, reg.d);

		//! 13; RL e: The contents of e are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x13:
			return RL(reg, reg.e);

		//! 14; RL h: The contents of h are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x14:
			return RL(reg, reg.h);

		//! 15; RL l: The contents of l are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x15:
			return RL(reg, reg.l);

		//! 16; RL (hl): The contents of (hl) are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x16:
			return executeOnPtr(cpu, reg.hl, RL, reg);

		//! 17; RL a: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x17:
			return RL(reg, reg.a);

		//! 18; RR b: The contents of b are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x18:
			return RR(reg, reg.b);

		//! 19; RR c: The contents of c are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x19:
			return RR(reg, reg.c);

		//! 1A; RR d: The contents of d are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x1A:
			return RR(reg, reg.d);

		//! 1B; RR e: The contents of e are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x1B:
			return RR(reg, reg.e);

		//! 1C; RR h: The contents of h are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x1C:
			return RR(reg, reg.h);

		//! 1D; RR l: The contents of l are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x1D:
			return RR(reg, reg.l);

		//! 1E; RR (hl): The contents of (hl) are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x1E:
			return executeOnPtr(cpu, reg.hl, RR, reg);

		//! 1F; RR a: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x1F:
			return RR(reg, reg.a);

		//! 20; SLA b: The contents of b are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.
		case 0x20:
			return SLA(reg, reg.b);

		//! 21; SLA c: The contents of c are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.
		case 0x21:
			return SLA(reg, reg.c);

		//! 22; SLA d: The contents of d are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.
		case 0x22:
			return SLA(reg, reg.d);

		//! 23; SLA e: The contents of e are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.
		case 0x23:
			return SLA(reg, reg.e);

		//! 24; SLA h: The contents of h are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.
		case 0x24:
			return SLA(reg, reg.h);

		//! 25; SLA l: The contents of l are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.
		case 0x25:
			return SLA(reg, reg.l);

		//! 26; SLA (hl): The contents of (hl) are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.
		case 0x26:
			return executeOnPtr(cpu, reg.hl, SLA, reg);

		//! 27; SLA a: The contents of a are shifted left one bit position. The contents of bit 7 are copied to the carry flag and a zero is put into bit 0.
		case 0x27:
			return SLA(reg, reg.a);

		//! 28; SRA b: The contents of b are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.
		case 0x28:
			return SRA(reg, reg.b);

		//! 29; SRA c: The contents of c are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.
		case 0x29:
			return SRA(reg, reg.c);

		//! 2A; SRA d: The contents of d are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.
		case 0x2A:
			return SRA(reg, reg.d);

		//! 2B; SRA e: The contents of e are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.
		case 0x2B:
			return SRA(reg, reg.e);

		//! 2C; SRA h: The contents of h are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.
		case 0x2C:
			return SRA(reg, reg.h);

		//! 2D; SRA l: The contents of l are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.
		case 0x2D:
			return SRA(reg, reg.l);

		//! 2E; SRA (hl): The contents of (hl) are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.
		case 0x2E:
			return executeOnPtr(cpu, reg.hl, SRA, reg);

		//! 2F; SRA a: The contents of a are shifted right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of bit 7 are unchanged.
		case 0x2F:
			return SRA(reg, reg.a);

		//! 30; SWAP b: The contents of b are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.
		case 0x30:
			return SWAP(reg, reg.b);

		//! 31; SWAP c: The contents of c are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.
		case 0x31:
			return SWAP(reg, reg.c);

		//! 32; SWAP d: The contents of d are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.
		case 0x32:
			return SWAP(reg, reg.d);

		//! 33; SWAP e: The contents of e are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.
		case 0x33:
			return SWAP(reg, reg.e);

		//! 34; SWAP h: The contents of h are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.
		case 0x34:
			return SWAP(reg, reg.h);

		//! 35; SWAP l: The contents of l are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.
		case 0x35:
			return SWAP(reg, reg.l);

		//! 36; SWAP (hl): The contents of (hl) are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.
		case 0x36:
			return executeOnPtr(cpu, reg.hl, SWAP, reg);

		//! 37; SWAP a: The contents of a are shifted left one bit position. The contents of bit 7 are put into the carry flag and a one is put into bit 0.
		case 0x37:
			return SWAP(reg, reg.a);

		//! 38; SRL b: The contents of b are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.
		case 0x38:
			return SRL(reg, reg.b);

		//! 39; SRL c: The contents of c are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.
		case 0x39:
			return SRL(reg, reg.c);

		//! 3A; SRL d: The contents of d are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.
		case 0x3A:
			return SRL(reg, reg.d);

		//! 3B; SRL e: The contents of e are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.
		case 0x3B:
			return SRL(reg, reg.e);

		//! 3C; SRL h: The contents of h are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.
		case 0x3C:
			return SRL(reg, reg.h);

		//! 3D; SRL l: The contents of l are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.
		case 0x3D:
			return SRL(reg, reg.l);

		//! 3E; SRL (hl): The contents of (hl) are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.
		case 0x3E:
			return executeOnPtr(cpu, reg.hl, SRL, reg);

		//! 3F; SRL a: The contents of a are shifted right one bit position. The contents of bit 0 are copied to the carry flag and a zero is put into bit 7.
		case 0x3F:
			return SRL(reg, reg.a);

		//! 40; BIT 0,b: Tests bit 0 of b.
		case 0x40:
			return BIT(reg, reg.b, 0);

		//! 41; BIT 0,c: Tests bit 0 of c.
		case 0x41:
			return BIT(reg, reg.c, 0);

		//! 42; BIT 0,d: Tests bit 0 of d.
		case 0x42:
			return BIT(reg, reg.d, 0);

		//! 43; BIT 0,e: Tests bit 0 of e.
		case 0x43:
			return BIT(reg, reg.e, 0);

		//! 44; BIT 0,h: Tests bit 0 of h.
		case 0x44:
			return BIT(reg, reg.h, 0);

		//! 45; BIT 0,l: Tests bit 0 of l.
		case 0x45:
			return BIT(reg, reg.l, 0);

		//! 46; BIT 0,(hl): Tests bit 0 of (hl).
		case 0x46:
			return BIT(reg, cpu.read(reg.hl), 0) + INDIRECTION_CYCLE_DURATION;

		//! 47; BIT 0,a: Tests bit 0 of a.
		case 0x47:
			return BIT(reg, reg.a, 0);

		//! 48; BIT 1,b: Tests bit 1 of b.
		case 0x48:
			return BIT(reg, reg.b, 1);

		//! 49; BIT 1,c: Tests bit 1 of c.
		case 0x49:
			return BIT(reg, reg.c, 1);

		//! 4A; BIT 1,d: Tests bit 1 of d.
		case 0x4A:
			return BIT(reg, reg.d, 1);

		//! 4B; BIT 1,e: Tests bit 1 of e.
		case 0x4B:
			return BIT(reg, reg.e, 1);

		//! 4C; BIT 1,h: Tests bit 1 of h.
		case 0x4C:
			return BIT(reg, reg.h, 1);

		//! 4D; BIT 1,l: Tests bit 1 of l.
		case 0x4D:
			return BIT(reg, reg.l, 1);

		//! 4E; BIT 1,(hl): Tests bit 1 of (hl).
		case 0x4E:
			return BIT(reg, cpu.read(reg.hl), 1) + INDIRECTION_CYCLE_DURATION;

		//! 4F; BIT 1,a: Tests bit 1 of a.
		case 0x4F:
			return BIT(reg, reg.a, 1);

		//! 50; BIT 2,b: Tests bit 2 of b.
		case 0x50:
			return BIT(reg, reg.b, 2);

		//! 51; BIT 2,c: Tests bit 2 of c.
		case 0x51:
			return BIT(reg, reg.c, 2);

		//! 52; BIT 2,d: Tests bit 2 of d.
		case 0x52:
			return BIT(reg, reg.d, 2);

		//! 53; BIT 2,e: Tests bit 2 of e.
		case 0x53:
			return BIT(reg, reg.e, 2);

		//! 54; BIT 2,h: Tests bit 2 of h.
		case 0x54:
			return BIT(reg, reg.h, 2);

		//! 55; BIT 2,l: Tests bit 2 of l.
		case 0x55:
			return BIT(reg, reg.l, 2);

		//! 56; BIT 2,(hl): Tests bit 2 of (hl).
		case 0x56:
			return BIT(reg, cpu.read(reg.hl), 2) + INDIRECTION_CYCLE_DURATION;

		//! 57; BIT 2,a: Tests bit 2 of a.
		case 0x57:
			return BIT(reg, reg.a, 2);

		//! 58; BIT 3,b: Tests bit 3 of b.
		case 0x58:
			return BIT(reg, reg.b, 3);

		//! 59; BIT 3,c: Tests bit 3 of c.
		case 0x59:
			return BIT(reg, reg.c, 3);

		//! 5A; BIT 3,d: Tests bit 3 of d.
		case 0x5A:
			return BIT(reg, reg.d, 3);

		//! 5B; BIT 3,e: Tests bit 3 of e.
		case 0x5B:
			return BIT(reg, reg.e, 3);

		//! 5C; BIT 3,h: Tests bit 3 of h.
		case 0x5C:
			return BIT(reg, reg.h, 3);

		//! 5D; BIT 3,l: Tests bit 3 of l.
		case 0x5D:
			return BIT(reg, reg.l, 3);

		//! 5E; BIT 3,(hl): Tests bit 3 of (hl).
		case 0x5E:
			return BIT(reg, cpu.read(reg.hl), 3) + INDIRECTION_CYCLE_DURATION;

		//! 5F; BIT 3,a: Tests bit 3 of a.
		case 0x5F:
			return BIT(reg, reg.a, 3);

		//! 60; BIT 4,b: Tests bit 4 of b.
		case 0x60:
			return BIT(reg, reg.b, 4);

		//! 61; BIT 4,c: Tests bit 4 of c.
		case 0x61:
			return BIT(reg, reg.c, 4);

		//! 62; BIT 4,d: Tests bit 4 of d.
		case 0x62:
			return BIT(reg, reg.d, 4);

		//! 63; BIT 4,e: Tests bit 4 of e.
		case 0x63:
			return BIT(reg, reg.e, 4);

		//! 64; BIT 4,h: Tests bit 4 of h.
		case 0x64:
			return BIT(reg, reg.h, 4);

		//! 65; BIT 4,l: Tests bit 4 of l.
		case 0x65:
			return BIT(reg, reg.l, 4);

		//! 66; BIT 4,(hl): Tests bit 4 of (hl).
		case 0x66:
			return BIT(reg, cpu.read(reg.hl), 4) + INDIRECTION_CYCLE_DURATION;

		//! 67; BIT 4,a: Tests bit 4 of a.
		case 0x67:
			return BIT(reg, reg.a, 4);

		//! 68; BIT 5,b: Tests bit 5 of b.
		case 0x68:
			return BIT(reg, reg.b, 5);

		//! 69; BIT 5,c: Tests bit 5 of c.
		case 0x69:
			return BIT(reg, reg.c, 5);

		//! 6A; BIT 5,d: Tests bit 5 of d.
		case 0x6A:
			return BIT(reg, reg.d, 5);

		//! 6B; BIT 5,e: Tests bit 5 of e.
		case 0x6B:
			return BIT(reg, reg.e, 5);

		//! 6C; BIT 5,h: Tests bit 5 of h.
		case 0x6C:
			return BIT(reg, reg.h, 5);

		//! 6D; BIT 5,l: Tests bit 5 of l.
		case 0x6D:
			return BIT(reg, reg.l, 5);

		//! 6E; BIT 5,(hl): Tests bit 5 of (hl).
		case 0x6E:
			return BIT(reg, cpu.read(reg.hl), 5) + INDIRECTION_CYCLE_DURATION;

		//! 6F; BIT 5,a: Tests bit 5 of a.
		case 0x6F:
			return BIT(reg, reg.a, 5);

		//! 70; BIT 6,b: Tests bit 6 of b.
		case 0x70:
			return BIT(reg, reg.b, 6);

		//! 71; BIT 6,c: Tests bit 6 of c.
		case 0x71:
			return BIT(reg, reg.c, 6);

		//! 72; BIT 6,d: Tests bit 6 of d.
		case 0x72:
			return BIT(reg, reg.d, 6);

		//! 73; BIT 6,e: Tests bit 6 of e.
		case 0x73:
			return BIT(reg, reg.e, 6);

		//! 74; BIT 6,h: Tests bit 6 of h.
		case 0x74:
			return BIT(reg, reg.h, 6);

		//! 75; BIT 6,l: Tests bit 6 of l.
		case 0x75:
			return BIT(reg, reg.l, 6);

		//! 76; BIT 6,(hl): Tests bit 6 of (hl).
		case 0x76:
			return BIT(reg, cpu.read(reg.hl), 6) + INDIRECTION_CYCLE_DURATION;

		//! 77; BIT 6,a: Tests bit 6 of a.
		case 0x77:
			return BIT(reg, reg.a, 6);

		//! 78; BIT 7,b: Tests bit 7 of b.
		case 0x78:
			return BIT(reg, reg.b, 7);

		//! 79; BIT 7,c: Tests bit 7 of c.
		case 0x79:
			return BIT(reg, reg.c, 7);

		//! 7A; BIT 7,d: Tests bit 7 of d.
		case 0x7A:
			return BIT(reg, reg.d, 7);

		//! 7B; BIT 7,e: Tests bit 7 of e.
		case 0x7B:
			return BIT(reg, reg.e, 7);

		//! 7C; BIT 7,h: Tests bit 7 of h.
		case 0x7C:
			return BIT(reg, reg.h, 7);

		//! 7D; BIT 7,l: Tests bit 7 of l.
		case 0x7D:
			return BIT(reg, reg.l, 7);

		//! 7E; BIT 7,(hl): Tests bit 7 of (hl).
		case 0x7E:
			return BIT(reg, cpu.read(reg.hl), 7) + INDIRECTION_CYCLE_DURATION;

		//! 7F; BIT 7,a: Tests bit 7 of a.
		case 0x7F:
			return BIT(reg, reg.a, 7);

		//! 80; RES 0,b: Resets bit 0 of b.
		case 0x80:
			return RES(reg.b, 0);

		//! 81; RES 0,c: Resets bit 0 of c.
		case 0x81:
			return RES(reg.c, 0);

		//! 82; RES 0,d: Resets bit 0 of d.
		case 0x82:
			return RES(reg.d, 0);

		//! 83; RES 0,e: Resets bit 0 of e.
		case 0x83:
			return RES(reg.e, 0);

		//! 84; RES 0,h: Resets bit 0 of h.
		case 0x84:
			return RES(reg.h, 0);

		//! 85; RES 0,l: Resets bit 0 of l.
		case 0x85:
			return RES(reg.l, 0);

		//! 86; RES 0,(hl): Resets bit 0 of (hl).
		case 0x86:
			return executeOnPtr(cpu, reg.hl, RES, static_cast<unsigned char>(0));

		//! 87; RES 0,a: Resets bit 0 of a.
		case 0x87:
			return RES(reg.a, 0);

		//! 88; RES 1,b: Resets bit 1 of b.
		case 0x88:
			return RES(reg.b, 1);

		//! 89; RES 1,c: Resets bit 1 of c.
		case 0x89:
			return RES(reg.c, 1);

		//! 8A; RES 1,d: Resets bit 1 of d.
		case 0x8A:
			return RES(reg.d, 1);

		//! 8B; RES 1,e: Resets bit 1 of e.
		case 0x8B:
			return RES(reg.e, 1);

		//! 8C; RES 1,h: Resets bit 1 of h.
		case 0x8C:
			return RES(reg.h, 1);

		//! 8D; RES 1,l: Resets bit 1 of l.
		case 0x8D:
			return RES(reg.l, 1);

		//! 8E; RES 1,(hl): Resets bit 1 of (hl).
		case 0x8E:
			return executeOnPtr(cpu, reg.hl, RES, static_cast<unsigned char>(1));

		//! 8F; RES 1,a: Resets bit 1 of a.
		case 0x8F:
			return RES(reg.a, 1);

		//! 90; RES 2,b: Resets bit 2 of b.
		case 0x90:
			return RES(reg.b, 2);

		//! 91; RES 2,c: Resets bit 2 of c.
		case 0x91:
			return RES(reg.c, 2);

		//! 92; RES 2,d: Resets bit 2 of d.
		case 0x92:
			return RES(reg.d, 2);

		//! 93; RES 2,e: Resets bit 2 of e.
		case 0x93:
			return RES(reg.e, 2);

		//! 94; RES 2,h: Resets bit 2 of h.
		case 0x94:
			return RES(reg.h, 2);

		//! 95; RES 2,l: Resets bit 2 of l.
		case 0x95:
			return RES(reg.l, 2);

		//! 96; RES 2,(hl): Resets bit 2 of (hl).
		case 0x96:
			return executeOnPtr(cpu, reg.hl, RES, static_cast<unsigned char>(2));

		//! 97; RES 2,a: Resets bit 2 of a.
		case 0x97:
			return RES(reg.a, 2);

		//! 98; RES 3,b: Resets bit 3 of b.
		case 0x98:
			return RES(reg.b, 3);

		//! 99; RES 3,c: Resets bit 3 of c.
		case 0x99:
			return RES(reg.c, 3);

		//! 9A; RES 3,d: Resets bit 3 of d.
		case 0x9A:
			return RES(reg.d, 3);

		//! 9B; RES 3,e: Resets bit 3 of e.
		case 0x9B:
			return RES(reg.e, 3);

		//! 9C; RES 3,h: Resets bit 3 of h.
		case 0x9C:
			return RES(reg.h, 3);

		//! 9D; RES 3,l: Resets bit 3 of l.
		case 0x9D:
			return RES(reg.l, 3);

		//! 9E; RES 3,(hl): Resets bit 3 of (hl).
		case 0x9E:
			return executeOnPtr(cpu, reg.hl, RES, static_cast<unsigned char>(3));

		//! 9F; RES 3,a: Resets bit 3 of a.
		case 0x9F:
			return RES(reg.a, 3);

		//! A0; RES 4,b: Resets bit 4 of b.
		case 0xA0:
			return RES(reg.b, 4);

		//! A1; RES 4,c: Resets bit 4 of c.
		case 0xA1:
			return RES(reg.c, 4);

		//! A2; RES 4,d: Resets bit 4 of d.
		case 0xA2:
			return RES(reg.d, 4);

		//! A3; RES 4,e: Resets bit 4 of e.
		case 0xA3:
			return RES(reg.e, 4);

		//! A4; RES 4,h: Resets bit 4 of h.
		case 0xA4:
			return RES(reg.h, 4);

		//! A5; RES 4,l: Resets bit 4 of l.
		case 0xA5:
			return RES(reg.l, 4);

		//! A6; RES 4,(hl): Resets bit 4 of (hl).
		case 0xA6:
			return executeOnPtr(cpu, reg.hl, RES, static_cast<unsigned char>(4));

		//! A7; RES 4,a: Resets bit 4 of a.
		case 0xA7:
			return RES(reg.a, 4);

		//! A8; RES 5,b: Resets bit 5 of b.
		case 0xA8:
			return RES(reg.b, 5);

		//! A9; RES 5,c: Resets bit 5 of c.
		case 0xA9:
			return RES(reg.c, 5);

		//! AA; RES 5,d: Resets bit 5 of d.
		case 0xAA:
			return RES(reg.d, 5);

		//! AB; RES 5,e: Resets bit 5 of e.
		case 0xAB:
			return RES(reg.e, 5);

		//! AC; RES 5,h: Resets bit 5 of h.
		case 0xAC:
			return RES(reg.h, 5);

		//! AD; RES 5,l: Resets bit 5 of l.
		case 0xAD:
			return RES(reg.l, 5);

		//! AE; RES 5,(hl): Resets bit 5 of (hl).
		case 0xAE:
			return executeOnPtr(cpu, reg.hl, RES, static_cast<unsigned char>(5));

		//! AF; RES 5,a: Resets bit 5 of a.
		case 0xAF:
			return RES(reg.a, 5);

		//! B0; RES 6,b: Resets bit 6 of b.
		case 0xB0:
			return RES(reg.b, 6);

		//! B1; RES 6,c: Resets bit 6 of c.
		case 0xB1:
			return RES(reg.c, 6);

		//! B2; RES 6,d: Resets bit 6 of d.
		case 0xB2:
			return RES(reg.d, 6);

		//! B3; RES 6,e: Resets bit 6 of e.
		case 0xB3:
			return RES(reg.e, 6);

		//! B4; RES 6,h: Resets bit 6 of h.
		case 0xB4:
			return RES(reg.h, 6);

		//! B5; RES 6,l: Resets bit 6 of l.
		case 0xB5:
			return RES(reg.l, 6);

		//! B6; RES 6,(hl): Resets bit 6 of (hl).
		case 0xB6:
			return executeOnPtr(cpu, reg.hl, RES, static_cast<unsigned char>(6));

		//! B7; RES 6,a: Resets bit 6 of a.
		case 0xB7:
			return RES(reg.a, 6);

		//! B8; RES 7,b: Resets bit 7 of b.
		case 0xB8:
			return RES(reg.b, 7);

		//! B9; RES 7,c: Resets bit 7 of c.
		case 0xB9:
			return RES(reg.c, 7);

		//! BA; RES 7,d: Resets bit 7 of d.
		case 0xBA:
			return RES(reg.d, 7);

		//! BB; RES 7,e: Resets bit 7 of e.
		case 0xBB:
			return RES(reg.e, 7);

		//! BC; RES 7,h: Resets bit 7 of h.
		case 0xBC:
			return RES(reg.h, 7);

		//! BD; RES 7,l: Resets bit 7 of l.
		case 0xBD:
			return RES(reg.l, 7);

		//! BE; RES 7,(hl): Resets bit 7 of (hl).
		case 0xBE:
			return executeOnPtr(cpu, reg.hl, RES, static_cast<unsigned char>(7));

		//! BF; RES 7,a: Resets bit 7 of a.
		case 0xBF:
			return RES(reg.a, 7);

		//! C0; SET 0,b: Sets bit 0 of b.
		case 0xC0:
			return SETB(reg.b, 0);

		//! C1; SET 0,c: Sets bit 0 of c.
		case 0xC1:
			return SETB(reg.c, 0);

		//! C2; SET 0,d: Sets bit 0 of d.
		case 0xC2:
			return SETB(reg.d, 0);

		//! C3; SET 0,e: Sets bit 0 of e.
		case 0xC3:
			return SETB(reg.e, 0);

		//! C4; SET 0,h: Sets bit 0 of h.
		case 0xC4:
			return SETB(reg.h, 0);

		//! C5; SET 0,l: Sets bit 0 of l.
		case 0xC5:
			return SETB(reg.l, 0);

		//! C6; SET 0,(hl): Sets bit 0 of (hl).
		case 0xC6:
			return executeOnPtr(cpu, reg.hl, SETB, static_cast<unsigned char>(0));

		//! C7; SET 0,a: Sets bit 0 of a.
		case 0xC7:
			return SETB(reg.a, 0);

		//! C8; SET 1,b: Sets bit 1 of b.
		case 0xC8:
			return SETB(reg.b, 1);

		//! C9; SET 1,c: Sets bit 1 of c.
		case 0xC9:
			return SETB(reg.c, 1);

		//! CA; SET 1,d: Sets bit 1 of d.
		case 0xCA:
			return SETB(reg.d, 1);

		//! CB; SET 1,e: Sets bit 1 of e.
		case 0xCB:
			return SETB(reg.e, 1);

		//! CC; SET 1,h: Sets bit 1 of h.
		case 0xCC:
			return SETB(reg.h, 1);

		//! CD; SET 1,l: Sets bit 1 of l.
		case 0xCD:
			return SETB(reg.l, 1);

		//! CE; SET 1,(hl): Sets bit 1 of (hl).
		case 0xCE:
			return executeOnPtr(cpu, reg.hl, SETB, static_cast<unsigned char>(1));

		//! CF; SET 1,a: Sets bit 1 of a.
		case 0xCF:
			return SETB(reg.a, 1);

		//! D0; SET 2,b: Sets bit 2 of b.
		case 0xD0:
			return SETB(reg.b, 2);

		//! D1; SET 2,c: Sets bit 2 of c.
		case 0xD1:
			return SETB(reg.c, 2);

		//! D2; SET 2,d: Sets bit 2 of d.
		case 0xD2:
			return SETB(reg.d, 2);

		//! D3; SET 2,e: Sets bit 2 of e.
		case 0xD3:
			return SETB(reg.e, 2);

		//! D4; SET 2,h: Sets bit 2 of h.
		case 0xD4:
			return SETB(reg.h, 2);

		//! D5; SET 2,l: Sets bit 2 of l.
		case 0xD5:
			return SETB(reg.l, 2);

		//! D6; SET 2,(hl): Sets bit 2 of (hl).
		case 0xD6:
			return executeOnPtr(cpu, reg.hl, SETB, static_cast<unsigned char>(2));

		//! D7; SET 2,a: Sets bit 2 of a.
		case 0xD7:
			return SETB(reg.a, 2);

		//! D8; SET 3,b: Sets bit 3 of b.
		case 0xD8:
			return SETB(reg.b, 3);

		//! D9; SET 3,c: Sets bit 3 of c.
		case 0xD9:
			return SETB(reg.c, 3);

		//! DA; SET 3,d: Sets bit 3 of d.
		case 0xDA:
			return SETB(reg.d, 3);

		//! DB; SET 3,e: Sets bit 3 of e.
		case 0xDB:
			return SETB(reg.e, 3);

		//! DC; SET 3,h: Sets bit 3 of h.
		case 0xDC:
			return SETB(reg.h, 3);

		//! DD; SET 3,l: Sets bit 3 of l.
		case 0xDD:
			return SETB(reg.l, 3);

		//! DE; SET 3,(hl): Sets bit 3 of (hl).
		case 0xDE:
			return executeOnPtr(cpu, reg.hl, SETB, static_cast<unsigned char>(3));

		//! DF; SET 3,a: Sets bit 3 of a.
		case 0xDF:
			return SETB(reg.a, 3);

		//! E0; SET 4,b: Sets bit 4 of b.
		case 0xE0:
			return SETB(reg.b, 4);

		//! E1; SET 4,c: Sets bit 4 of c.
		case 0xE1:
			return SETB(reg.c, 4);

		//! E2; SET 4,d: Sets bit 4 of d.
		case 0xE2:
			return SETB(reg.d, 4);

		//! E3; SET 4,e: Sets bit 4 of e.
		case 0xE3:
			return SETB(reg.e, 4);

		//! E4; SET 4,h: Sets bit 4 of h.
		case 0xE4:
			return SETB(reg.h, 4);

		//! E5; SET 4,l: Sets bit 4 of l.
		case 0xE5:
			return SETB(reg.l, 4);

		//! E6; SET 4,(hl): Sets bit 4 of (hl).
		case 0xE6:
			return executeOnPtr(cpu, reg.hl, SETB, static_cast<unsigned char>(4));

		//! E7; SET 4,a: Sets bit 4 of a.
		case 0xE7:
			return SETB(reg.a, 4);

		//! E8; SET 5,b: Sets bit 5 of b.
		case 0xE8:
			return SETB(reg.b, 5);

		//! E9; SET 5,c: Sets bit 5 of c.
		case 0xE9:
			return SETB(reg.c, 5);

		//! EA; SET 5,d: Sets bit 5 of d.
		case 0xEA:
			return SETB(reg.d, 5);

		//! EB; SET 5,e: Sets bit 5 of e.
		case 0xEB:
			return SETB(reg.e, 5);

		//! EC; SET 5,h: Sets bit 5 of h.
		case 0xEC:
			return SETB(reg.h, 5);

		//! ED; SET 5,l: Sets bit 5 of l.
		case 0xED:
			return SETB(reg.l, 5);

		//! EE; SET 5,(hl): Sets bit 5 of (hl).
		case 0xEE:
			return executeOnPtr(cpu, reg.hl, SETB, static_cast<unsigned char>(5));

		//! EF; SET 5,a: Sets bit 5 of a.
		case 0xEF:
			return SETB(reg.a, 5);

		//! F0; SET 6,b: Sets bit 6 of b.
		case 0xF0:
			return SETB(reg.b, 6);

		//! F1; SET 6,c: Sets bit 6 of c.
		case 0xF1:
			return SETB(reg.c, 6);

		//! F2; SET 6,d: Sets bit 6 of d.
		case 0xF2:
			return SETB(reg.d, 6);

		//! F3; SET 6,e: Sets bit 6 of e.
		case 0xF3:
			return SETB(reg.e, 6);

		//! F4; SET 6,h: Sets bit 6 of h.
		case 0xF4:
			return SETB(reg.h, 6);

		//! F5; SET 6,l: Sets bit 6 of l.
		case 0xF5:
			return SETB(reg.l, 6);

		//! F6; SET 6,(hl): Sets bit 6 of (hl).
		case 0xF6:
			return executeOnPtr(cpu, reg.hl, SETB, static_cast<unsigned char>(6));

		//! F7; SET 6,a: Sets bit 6 of a.
		case 0xF7:
			return SETB(reg.a, 6);

		//! F8; SET 7,b: Sets bit 7 of b.
		case 0xF8:
			return SETB(reg.b, 7);

		//! F9; SET 7,c: Sets bit 7 of c.
		case 0xF9:
			return SETB(reg.c, 7);

		//! FA; SET 7,d: Sets bit 7 of d.
		case 0xFA:
			return SETB(reg.d, 7);

		//! FB; SET 7,e: Sets bit 7 of e.
		case 0xFB:
			return SETB(reg.e, 7);

		//! FC; SET 7,h: Sets bit 7 of h.
		case 0xFC:
			return SETB(reg.h, 7);

		//! FD; SET 7,l: Sets bit 7 of l.
		case 0xFD:
			return SETB(reg.l, 7);

		//! FE; SET 7,(hl): Sets bit 7 of (hl).
		case 0xFE:
			return executeOnPtr(cpu, reg.hl, SETB, static_cast<unsigned char>(7));

		//! FF; SET 7,a: Sets bit 7 of a.
		case 0xFF:
			return SETB(reg.a, 7);
		default:  // Impossible to reach, just here for make compiler happy
			return 0;
		}
	}
}