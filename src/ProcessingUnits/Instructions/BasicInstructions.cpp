/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** BasicInstructions.cpp
*/

#include "CPUInstructions.hpp"
#include "Instructions.hpp"

namespace GBEmulator::Instructions {
	unsigned executeInstruction(unsigned char opcode, CPU &cpu, CPU::Registers &reg)
	{
		switch (opcode) {
		//! 00; NOP: do nothing
		case 0x00:
			return NOP_CYCLE_DURATION;

		//! 01; LD bc,**: Loads ** into bc.
		case 0x01:
			return LD16(reg.bc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! 02; LD (bc), a: Stores a into the memory location pointed to by bc
		case 0x02:
			return LD8toPTR(cpu, reg.bc, reg.a);

		//! 03; INC bc: Adds one to bc.
		case 0x03:
			return INC16(reg.bc);

		//! 04; INC b: Adds one to b.
		case 0x04:
			return INC8(reg, reg.b);

		//! 05; DEC b: Subtracts one from b.
		case 0x05:
			return DEC8(reg, reg.b);

		//! 06; LD b,*: Loads * into b.
		case 0x06:
			return LD8(reg.b, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 07; RLCA: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.
		case 0x07:
			return RLCA(reg);

		//! 08; LD (**), SP: Load the value pointed to by ** to sp
		case 0x08:
			return LD16toPTR(cpu, cpu.fetchArgument16(), reg.sp) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! 09; ADD hl,bc: The value of bc is added to hl.
		case 0x09:
			return ADD16(reg, reg.hl, reg.bc);

		//! 0A; LD a,(bc): Loads the value pointed to by bc into a.
		case 0x0A:
			return LD8fromPTR(cpu, reg.a, reg.bc);

		//! 0B; DEC bc: Subtracts one from bc.
		case 0x0B:
			return DEC16(reg.bc);

		//! 0C; INC c: Adds one to c.
		case 0x0C:
			return INC8(reg, reg.c);

		//! 0D; DEC c: Subtracts one from c.
		case 0x0D:
			return DEC8(reg, reg.c);

		//! 0E; LD c,*: Loads * into c.
		case 0x0E:
			return LD8(reg.c, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 0F; RRCA: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.
		case 0x0F:
			return RRCA(reg);

		//! 10; STOP: Halts the CPU until a key is pressed
		case 0x10:
			return STOP(cpu);

		//! 11; LD de,**: Loads ** into de.
		case 0x11:
			return LD16(reg.de, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! 12; LD (de),a: Stores a into the memory location pointed to by de.
		case 0x12:
			return LD8toPTR(cpu, reg.de, reg.a);

		//! 13; INC de: Adds one to de.
		case 0x13:
			return INC16(reg.de);

		//! 14; INC d: Adds one to d.
		case 0x14:
			return INC8(reg, reg.d);

		//! 15; DEC d: Subtracts one from d.
		case 0x15:
			return DEC8(reg, reg.d);

		//! 16; LD d,*: Loads * into d.
		case 0x16:
			return LD8(reg.d, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 17; RLA: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.
		case 0x17:
			return RLA(reg);

		//! 18; JR *: The signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		case 0x18:
			return JR(reg, true, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 19; ADD hl,de: The value of de is added to hl.
		case 0x19:
			return ADD16(reg, reg.hl, reg.de);

		//! 1A; LD a,(de): Loads the value pointed to by de into a.
		case 0x1A:
			return LD8fromPTR(cpu, reg.a, reg.de);

		//! 1B; DEC de: Subtracts one from de.
		case 0x1B:
			return DEC16(reg.de);

		//! 1C; INC e: Adds one to e.
		case 0x1C:
			return INC8(reg, reg.e);

		//! 1D; DEC e: Subtracts one from e.
		case 0x1D:
			return DEC8(reg, reg.e);

		//! 1E; LD e,*: Loads * into e.
		case 0x1E:
			return LD8(reg.e, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 1F; RRA: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.
		case 0x1F:
			return RRA(reg);

		//! 20; JR nz,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		case 0x20:
			return JR(reg, !reg.fz, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 21; LD hl, **: Loads ** into hl register
		case 0x21:
			return LD16(reg.hl, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! 22; LDI (hl),a: Loads a to the address pointed to by hl and increment hl
		case 0x22:
			return LD8toPTR(cpu, reg.hl++, reg.a);

		//! 23; INC hl: Adds one to hl.
		case 0x23:
			return INC16(reg.hl);

		//! 24; INC h: Adds one to h.
		case 0x24:
			return INC8(reg, reg.h);

		//! 25; DEC h: Subtracts one from h.
		case 0x25:
			return DEC8(reg, reg.h);

		//! 26; LD h,*: Loads * into h.
		case 0x26:
			return LD8(reg.h, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 27; DAA: Adjusts a for BCD addition and subtraction operations.
		case 0x27:
			return DAA(reg, reg.a);

		//! 28; JR z,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		case 0x28:
			return JR(reg, reg.fz, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 29; ADD hl,hl: The value of hl is added to hl.
		case 0x29:
			return ADD16(reg, reg.hl, reg.hl);

		//! 2A; LDI a,(hl): Loads the value pointed to by hl to a and increments hl
		case 0x2A:
			return LD8fromPTR(cpu, reg.a, reg.hl++);

		//! 2B; DEC hl: Subtracts one from hl.
		case 0x2B:
			return DEC16(reg.hl);

		//! 2C; INC l: Adds one to l.
		case 0x2C:
			return INC8(reg, reg.l);

		//! 2D; DEC l: Subtracts one from l.
		case 0x2D:
			return DEC8(reg, reg.l);

		//! 2E; LD l,*: Loads * into l.
		case 0x2E:
			return LD8(reg.l, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 2F; CPL: The contents of a are inverted (one's complement).
		case 0x2F:
			return CPL(reg);

		//! 30; JR nc,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		case 0x30:
			return JR(reg, !reg.fc, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 31; LD sp, **: Loads ** into sp register
		case 0x31:
			return LD16(reg.sp, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! 32; LD (hl-), a: Loads a into address pointed to by hl and decrement hl
		case 0x32:
			return LD8toPTR(cpu, reg.hl--, reg.a);

		//! 33; INC sp: Adds one to sp.
		case 0x33:
			return INC16(reg.sp);

		//! 34; INC (hl): Adds one to (hl).
		case 0x34:
			return INCPTR(cpu, reg, reg.hl);

		//! 35; DEC (hl): Subtracts one from (hl).
		case 0x35:
			return DECPTR(cpu, reg, reg.hl);

		//! 36; LD (hl),*: Loads * into (hl).
		case 0x36:
			return LD8toPTR(cpu, reg.hl, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 37; SCF: Sets the carry flag.
		case 0x37:
			return setFlags(reg, UNCHANGED, UNSET, UNSET, SET), BASIC_BIT_OPERATION_CYCLE_DURATION;

		//! 38; JR c,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		case 0x38:
			return JR(reg, reg.fc, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 39; ADD hl,sp: The value of sp is added to hl.
		case 0x39:
			return ADD16(reg, reg.hl, reg.sp);

		//! 3A; LDD a,(hl): Load the value pointed to by hl to a and decrements hl
		case 0x3A:
			return LD8fromPTR(cpu, reg.a, reg.hl--) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! 3B; DEC sp: Subtracts one from sp.
		case 0x3B:
			return DEC16(reg.sp);

		//! 3C; INC a: Adds one to a.
		case 0x3C:
			return INC8(reg, reg.a);

		//! 3D; DEC a: Subtracts one from a.
		case 0x3D:
			return DEC8(reg, reg.a);

		//! 3E; LD a,*: Loads * into a.
		case 0x3E:
			return LD8(reg.a, cpu.fetchArgument()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! 3F; CCF: Inverts the carry flag.
		case 0x3F:
			return setFlags(reg, UNCHANGED, UNSET, UNSET, reg.fc ? UNSET : SET), BASIC_BIT_OPERATION_CYCLE_DURATION;

		//! 40; LD b,b: The contents of b are loaded into b.
		case 0x40:
			return LD8(reg.b, reg.b);

		//! 41; LD b,c: The contents of c are loaded into b.
		case 0x41:
			return LD8(reg.b, reg.c);

		//! 42; LD b,d: The contents of d are loaded into b.
		case 0x42:
			return LD8(reg.b, reg.d);

		//! 43; LD b,e: The contents of e are loaded into b.
		case 0x43:
			return LD8(reg.b, reg.e);

		//! 44; LD b,h: The contents of h are loaded into b.
		case 0x44:
			return LD8(reg.b, reg.h);

		//! 45; LD b,l: The contents of l are loaded into b.
		case 0x45:
			return LD8(reg.b, reg.l);

		//! 46; LD b,(hl): The contents of (hl) are loaded into b.
		case 0x46:
			return LD8fromPTR(cpu, reg.b, reg.hl);

		//! 47; LD b,a: The contents of a are loaded into b.
		case 0x47:
			return LD8(reg.b, reg.a);

		//! 48; LD c,b: The contents of b are loaded into c.
		case 0x48:
			return LD8(reg.c, reg.b);

		//! 49; LD c,c: The contents of c are loaded into c.
		case 0x49:
			return LD8(reg.c, reg.c);

		//! 4A; LD c,d: The contents of d are loaded into c.
		case 0x4A:
			return LD8(reg.c, reg.d);

		//! 4B; LD c,e: The contents of e are loaded into c.
		case 0x4B:
			return LD8(reg.c, reg.e);

		//! 4C; LD c,h: The contents of h are loaded into c.
		case 0x4C:
			return LD8(reg.c, reg.h);

		//! 4D; LD c,l: The contents of l are loaded into c.
		case 0x4D:
			return LD8(reg.c, reg.l);

		//! 4E; LD c,(hl): The contents of (hl) are loaded into c.
		case 0x4E:
			return LD8fromPTR(cpu, reg.c, reg.hl);

		//! 4F; LD c,a: The contents of a are loaded into c.
		case 0x4F:
			return LD8(reg.c, reg.a);

		//! 50; LD d,b: The contents of b are loaded into d.
		case 0x50:
			return LD8(reg.d, reg.b);

		//! 51; LD d,c: The contents of c are loaded into d.
		case 0x51:
			return LD8(reg.d, reg.c);

		//! 52; LD d,d: The contents of d are loaded into d.
		case 0x52:
			return LD8(reg.d, reg.d);

		//! 53; LD d,e: The contents of e are loaded into d.
		case 0x53:
			return LD8(reg.d, reg.e);

		//! 54; LD d,h: The contents of h are loaded into d.
		case 0x54:
			return LD8(reg.d, reg.h);

		//! 55; LD d,l: The contents of l are loaded into d.
		case 0x55:
			return LD8(reg.d, reg.l);

		//! 56; LD d,(hl): The contents of (hl) are loaded into d.
		case 0x56:
			return LD8fromPTR(cpu, reg.d, reg.hl);

		//! 57; LD d,a: The contents of a are loaded into d.
		case 0x57:
			return LD8(reg.d, reg.a);

		//! 58; LD e,b: The contents of b are loaded into e.
		case 0x58:
			return LD8(reg.e, reg.b);

		//! 59; LD e,c: The contents of c are loaded into e.
		case 0x59:
			return LD8(reg.e, reg.c);

		//! 5A; LD e,d: The contents of d are loaded into e.
		case 0x5A:
			return LD8(reg.e, reg.d);

		//! 5B; LD e,e: The contents of e are loaded into e.
		case 0x5B:
			return LD8(reg.e, reg.e);

		//! 5C; LD e,h: The contents of h are loaded into e.
		case 0x5C:
			return LD8(reg.e, reg.h);

		//! 5D; LD e,l: The contents of l are loaded into e.
		case 0x5D:
			return LD8(reg.e, reg.l);

		//! 5E; LD e,(hl): The contents of (hl) are loaded into e.
		case 0x5E:
			return LD8fromPTR(cpu, reg.e, reg.hl);

		//! 5F; LD e,a: The contents of a are loaded into e.
		case 0x5F:
			return LD8(reg.e, reg.a);

		//! 60; LD h,b: The contents of b are loaded into h.
		case 0x60:
			return LD8(reg.h, reg.b);

		//! 61; LD h,c: The contents of c are loaded into h.
		case 0x61:
			return LD8(reg.h, reg.c);

		//! 62; LD h,d: The contents of d are loaded into h.
		case 0x62:
			return LD8(reg.h, reg.d);

		//! 63; LD h,e: The contents of e are loaded into h.
		case 0x63:
			return LD8(reg.h, reg.e);

		//! 64; LD h,h: The contents of h are loaded into h.
		case 0x64:
			return LD8(reg.h, reg.h);

		//! 65; LD h,l: The contents of l are loaded into h.
		case 0x65:
			return LD8(reg.h, reg.l);

		//! 66; LD h,(hl): The contents of (hl) are loaded into h.
		case 0x66:
			return LD8fromPTR(cpu, reg.h, reg.hl);

		//! 67; LD h,a: The contents of a are loaded into h.
		case 0x67:
			return LD8(reg.h, reg.a);

		//! 68; LD l,b: The contents of b are loaded into l.
		case 0x68:
			return LD8(reg.l, reg.b);

		//! 69; LD l,c: The contents of c are loaded into l.
		case 0x69:
			return LD8(reg.l, reg.c);

		//! 6A; LD l,d: The contents of d are loaded into l.
		case 0x6A:
			return LD8(reg.l, reg.d);

		//! 6B; LD l,e: The contents of e are loaded into l.
		case 0x6B:
			return LD8(reg.l, reg.e);

		//! 6C; LD l,h: The contents of h are loaded into l.
		case 0x6C:
			return LD8(reg.l, reg.h);

		//! 6D; LD l,l: The contents of l are loaded into l.
		case 0x6D:
			return LD8(reg.l, reg.l);

		//! 6E; LD l,(hl): The contents of (hl) are loaded into l.
		case 0x6E:
			return LD8fromPTR(cpu, reg.l, reg.hl);

		//! 6F; LD l,a: The contents of a are loaded into l.
		case 0x6F:
			return LD8(reg.l, reg.a);

		//! 70; LD (hl),b: The contents of b are loaded into (hl).
		case 0x70:
			return LD8toPTR(cpu, reg.hl, reg.b);

		//! 71; LD (hl),c: The contents of c are loaded into (hl).
		case 0x71:
			return LD8toPTR(cpu, reg.hl, reg.c);

		//! 72; LD (hl),d: The contents of d are loaded into (hl).
		case 0x72:
			return LD8toPTR(cpu, reg.hl, reg.d);

		//! 73; LD (hl),e: The contents of e are loaded into (hl).
		case 0x73:
			return LD8toPTR(cpu, reg.hl, reg.e);

		//! 74; LD (hl),h: The contents of h are loaded into (hl).
		case 0x74:
			return LD8toPTR(cpu, reg.hl, reg.h);

		//! 75; LD (hl),l: The contents of l are loaded into (hl).
		case 0x75:
			return LD8toPTR(cpu, reg.hl, reg.l);

		//! 76; HALT: Suspends CPU operation until an interrupt or reset occurs.
		case 0x76:
			return cpu.halt(), LD_CYCLE_DURATION;

		//! 77; LD (hl),a: The contents of a are loaded into (hl).
		case 0x77:
			return LD8toPTR(cpu, reg.hl, reg.a);

		//! 78; LD a,b: The contents of b are loaded into a.
		case 0x78:
			return LD8(reg.a, reg.b);

		//! 79; LD a,c: The contents of c are loaded into a.
		case 0x79:
			return LD8(reg.a, reg.c);

		//! 7A; LD a,d: The contents of d are loaded into a.
		case 0x7A:
			return LD8(reg.a, reg.d);

		//! 7B; LD a,e: The contents of e are loaded into a.
		case 0x7B:
			return LD8(reg.a, reg.e);

		//! 7C; LD a,h: The contents of h are loaded into a.
		case 0x7C:
			return LD8(reg.a, reg.h);

		//! 7D; LD a,l: The contents of l are loaded into a.
		case 0x7D:
			return LD8(reg.a, reg.l);

		//! 7E; LD a,(hl): The contents of (hl) are loaded into a.
		case 0x7E:
			return LD8fromPTR(cpu, reg.a, reg.hl);

		//! 7F; LD a,a: The contents of a are loaded into a.
		case 0x7F:
			return LD8(reg.a, reg.a);

		//! 80; ADD a,b: Adds b to a.
		case 0x80:
			return ADD8(reg, reg.a, reg.b, false);

		//! 81; ADD a,c: Adds c to a.
		case 0x81:
			return ADD8(reg, reg.a, reg.c, false);

		//! 82; ADD a,d: Adds d to a.
		case 0x82:
			return ADD8(reg, reg.a, reg.d, false);

		//! 83; ADD a,e: Adds e to a.
		case 0x83:
			return ADD8(reg, reg.a, reg.e, false);

		//! 84; ADD a,h: Adds h to a.
		case 0x84:
			return ADD8(reg, reg.a, reg.h, false);

		//! 85; ADD a,l: Adds l to a.
		case 0x85:
			return ADD8(reg, reg.a, reg.l, false);

		//! 86; ADD a,(hl): Adds (hl) to a.
		case 0x86:
			return ADD8(reg, reg.a, cpu.read(reg.hl), false) + INDIRECTION_CYCLE_DURATION;

		//! 87; ADD a,a: Adds a to a.
		case 0x87:
			return ADD8(reg, reg.a, reg.a, false);

		//! 88; ADC a,b: Adds b and the carry flag to a.
		case 0x88:
			return ADD8(reg, reg.a, reg.b, reg.fc);

		//! 89; ADC a,c: Adds c and the carry flag to a.
		case 0x89:
			return ADD8(reg, reg.a, reg.c, reg.fc);

		//! 8A; ADC a,d: Adds d and the carry flag to a.
		case 0x8A:
			return ADD8(reg, reg.a, reg.d, reg.fc);

		//! 8B; ADC a,e: Adds e and the carry flag to a.
		case 0x8B:
			return ADD8(reg, reg.a, reg.e, reg.fc);

		//! 8C; ADC a,h: Adds h and the carry flag to a.
		case 0x8C:
			return ADD8(reg, reg.a, reg.h, reg.fc);

		//! 8D; ADC a,l: Adds l and the carry flag to a.
		case 0x8D:
			return ADD8(reg, reg.a, reg.l, reg.fc);

		//! 8E; ADC a,(hl): Adds (hl) and the carry flag to a.
		case 0x8E:
			return ADD8(reg, reg.a, cpu.read(reg.hl), reg.fc) + INDIRECTION_CYCLE_DURATION;

		//! 8F; ADC a,a: Adds a and the carry flag to a.
		case 0x8F:
			return ADD8(reg, reg.a, reg.a, reg.fc);

		//! 90; SUB b: Subtracts b from a.
		case 0x90:
			return SUB8(reg, reg.a, reg.b, false);

		//! 91; SUB c: Subtracts c from a.
		case 0x91:
			return SUB8(reg, reg.a, reg.c, false);

		//! 92; SUB d: Subtracts d from a.
		case 0x92:
			return SUB8(reg, reg.a, reg.d, false);

		//! 93; SUB e: Subtracts e from a.
		case 0x93:
			return SUB8(reg, reg.a, reg.e, false);

		//! 94; SUB h: Subtracts h from a.
		case 0x94:
			return SUB8(reg, reg.a, reg.h, false);

		//! 95; SUB l: Subtracts l from a.
		case 0x95:
			return SUB8(reg, reg.a, reg.l, false);

		//! 96; SUB (hl): Subtracts (hl) from a.
		case 0x96:
			return SUB8(reg, reg.a, cpu.read(reg.hl), false) + INDIRECTION_CYCLE_DURATION;

		//! 97; SUB a: Subtracts a from a.
		case 0x97:
			return SUB8(reg, reg.a, reg.a, false);

		//! 98; SBC a,b: Subtracts b and the carry flag from a.
		case 0x98:
			return SUB8(reg, reg.a, reg.b, reg.fc);

		//! 99; SBC a,c: Subtracts c and the carry flag from a.
		case 0x99:
			return SUB8(reg, reg.a, reg.c, reg.fc);

		//! 9A; SBC a,d: Subtracts d and the carry flag from a.
		case 0x9A:
			return SUB8(reg, reg.a, reg.d, reg.fc);

		//! 9B; SBC a,e: Subtracts e and the carry flag from a.
		case 0x9B:
			return SUB8(reg, reg.a, reg.e, reg.fc);

		//! 9C; SBC a,h: Subtracts h and the carry flag from a.
		case 0x9C:
			return SUB8(reg, reg.a, reg.h, reg.fc);

		//! 9D; SBC a,l: Subtracts l and the carry flag from a.
		case 0x9D:
			return SUB8(reg, reg.a, reg.l, reg.fc);

		//! 9E; SBC a,(hl): Subtracts (hl) and the carry flag from a.
		case 0x9E:
			return SUB8(reg, reg.a, cpu.read(reg.hl), reg.fc) + INDIRECTION_CYCLE_DURATION;

		//! 9F; SBC a,a: Subtracts a and the carry flag from a.
		case 0x9F:
			return SUB8(reg, reg.a, reg.a, reg.fc);

		//! A0; AND b: Bitwise AND on a with b.
		case 0xA0:
			return AND8(reg, reg.a, reg.b);

		//! A1; AND c: Bitwise AND on a with c.
		case 0xA1:
			return AND8(reg, reg.a, reg.c);

		//! A2; AND d: Bitwise AND on a with d.
		case 0xA2:
			return AND8(reg, reg.a, reg.d);

		//! A3; AND e: Bitwise AND on a with e.
		case 0xA3:
			return AND8(reg, reg.a, reg.e);

		//! A4; AND h: Bitwise AND on a with h.
		case 0xA4:
			return AND8(reg, reg.a, reg.h);

		//! A5; AND l: Bitwise AND on a with l.
		case 0xA5:
			return AND8(reg, reg.a, reg.l);

		//! A6; AND (hl): Bitwise AND on a with (hl).
		case 0xA6:
			return AND8(reg, reg.a, cpu.read(reg.hl)) + INDIRECTION_CYCLE_DURATION;

		//! A7; AND a: Bitwise AND on a with a.
		case 0xA7:
			return AND8(reg, reg.a, reg.a);

		//! A8; XOR b: Bitwise XOR on a with b.
		case 0xA8:
			return XOR(reg, reg.b);

		//! A9; XOR c: Bitwise XOR on a with c.
		case 0xA9:
			return XOR(reg, reg.c);

		//! AA; XOR d: Bitwise XOR on a with d.
		case 0xAA:
			return XOR(reg, reg.d);

		//! AB; XOR e: Bitwise XOR on a with e.
		case 0xAB:
			return XOR(reg, reg.e);

		//! AC; XOR h: Bitwise XOR on a with h.
		case 0xAC:
			return XOR(reg, reg.h);

		//! AD; XOR l: Bitwise XOR on a with l.
		case 0xAD:
			return XOR(reg, reg.l);

		//! AE; XOR (hl): Bitwise XOR on a with (hl).
		case 0xAE:
			return XOR(reg, cpu.read(reg.hl)) + INDIRECTION_CYCLE_DURATION;

		//! AF; XOR a: Bitwise XOR a with a
		case 0xAF:
			return XOR(reg, reg.a);

		//! B0; OR b: Bitwise OR on a with b.
		case 0xB0:
			return OR8(reg, reg.a, reg.b);

		//! B1; OR c: Bitwise OR on a with c.
		case 0xB1:
			return OR8(reg, reg.a, reg.c);

		//! B2; OR d: Bitwise OR on a with d.
		case 0xB2:
			return OR8(reg, reg.a, reg.d);

		//! B3; OR e: Bitwise OR on a with e.
		case 0xB3:
			return OR8(reg, reg.a, reg.e);

		//! B4; OR h: Bitwise OR on a with h.
		case 0xB4:
			return OR8(reg, reg.a, reg.h);

		//! B5; OR l: Bitwise OR on a with l.
		case 0xB5:
			return OR8(reg, reg.a, reg.l);

		//! B6; OR (hl): Bitwise OR on a with (hl).
		case 0xB6:
			return OR8(reg, reg.a, cpu.read(reg.hl)) + INDIRECTION_CYCLE_DURATION;

		//! B7; OR a: Bitwise OR on a with a.
		case 0xB7:
			return OR8(reg, reg.a, reg.a);

		//! B8; CP b: Subtracts b from a and affects flags according to the result. a is not modified.
		case 0xB8:
			return CP(reg, reg.b);

		//! B9; CP c: Subtracts c from a and affects flags according to the result. a is not modified.
		case 0xB9:
			return CP(reg, reg.c);

		//! BA; CP d: Subtracts d from a and affects flags according to the result. a is not modified.
		case 0xBA:
			return CP(reg, reg.d);

		//! BB; CP e: Subtracts e from a and affects flags according to the result. a is not modified.
		case 0xBB:
			return CP(reg, reg.e);

		//! BC; CP h: Subtracts h from a and affects flags according to the result. a is not modified.
		case 0xBC:
			return CP(reg, reg.h);

		//! BD; CP l: Subtracts l from a and affects flags according to the result. a is not modified.
		case 0xBD:
			return CP(reg, reg.l);

		//! BE; CP (hl): Subtracts (hl) from a and affects flags according to the result. a is not modified.
		case 0xBE:
			return CP(reg, cpu.read(reg.hl)) + INDIRECTION_CYCLE_DURATION;

		//! BF; CP a: Subtracts a from a and affects flags according to the result. a is not modified.
		case 0xBF:
			return CP(reg, reg.a);

		//! C0; RET nz: If condition cc is true, the top stack entry is popped into pc.
		case 0xC0:
			return RET(cpu, reg, !reg.fz);

		//! C1; POP bc: The memory location pointed to by sp is stored into c and sp is incremented. The memory location pointed to by sp is stored into b and sp is incremented again.
		case 0xC1:
			return POP(cpu, reg, reg.bc);

		//! C2; JP nz,**: If condition cc is true, ** is copied to pc.
		case 0xC2:
			return JP(reg, !reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! C3; JP **: ** is copied to pc.
		case 0xC3:
			return JP(reg, true, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! C4; CALL nz,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		case 0xC4:
			return CALLC(cpu, reg, !reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! C5; PUSH bc: sp is decremented and b is stored into the memory location pointed to by sp. sp is decremented again and c is stored into the memory location pointed to by sp.
		case 0xC5:
			return PUSH(cpu, reg, reg.bc);

		//! C6; ADD a,*: Adds * to a.
		case 0xC6:
			return ADD8(reg, reg.a, cpu.fetchArgument(), false) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! C7; RST 00h: The current pc value plus one is pushed onto the stack, then is loaded with 00h.
		case 0xC7:
			return CALL(cpu, reg, 0x00);

		//! C8; RET z: If condition cc is true, the top stack entry is popped into pc.
		case 0xC8:
			return RET(cpu, reg, reg.fz);

		//! C9; RET: The top stack entry is popped into pc.
		case 0xC9:
			return POP(cpu, reg, reg.pc) + BASIC_BIT_OPERATION_CYCLE_DURATION;

		//! CA; JP z,**: If condition cc is true, ** is copied to pc.
		case 0xCA:
			return JP(reg, reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! CB; Prefix for bit level instructions
		case 0xCB:
			return Instructions::executeBitInstruction(cpu.fetchArgument(), cpu, reg) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! CC; CALL z,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		case 0xCC:
			return CALLC(cpu, reg, reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! CD; CALL **: The current pc value plus three is pushed onto the stack, then is loaded with **.
		case 0xCD:
			return CALL(cpu, reg, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! CE; ADC a,*: Adds * and the carry flag to a.
		case 0xCE:
			return ADD8(reg, reg.a, cpu.fetchArgument(), reg.fc) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! CF; RST 08h: The current pc value plus one is pushed onto the stack, then is loaded with 08h.
		case 0xCF:
			return CALL(cpu, reg, 0x08);

		//! D0; RET nc: If condition cc is true, the top stack entry is popped into pc.
		case 0xD0:
			return RET(cpu, reg, !reg.fc);

		//! D1; POP de: The memory location pointed to by sp is stored into e and sp is incremented. The memory location pointed to by sp is stored into d and sp is incremented again.
		case 0xD1:
			return POP(cpu, reg, reg.de);

		//! D2; JP nc,**: If condition cc is true, ** is copied to pc.
		case 0xD2:
			return JP(reg, !reg.fc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! D4; CALL nc,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		case 0xD4:
			return CALLC(cpu, reg, !reg.fc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! D5; PUSH de: sp is decremented and d is stored into the memory location pointed to by sp. sp is decremented again and e is stored into the memory location pointed to by sp.
		case 0xD5:
			return PUSH(cpu, reg, reg.de);

		//! D6; SUB *: Subtracts * from a.
		case 0xD6:
			return SUB8(reg, reg.a, cpu.fetchArgument(), false) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! D7; RST 10h: The current pc value plus one is pushed onto the stack, then is loaded with 10h.
		case 0xD7:
			return CALL(cpu, reg, 0x10);

		//! D8; RET c: If condition cc is true, the top stack entry is popped into pc.
		case 0xD8:
			return RET(cpu, reg, reg.fc);

		//! D9; RETI
		case 0xD9:
			return cpu.setInterruptMaster(true), POP(cpu, reg, reg.pc) + BASIC_BIT_OPERATION_CYCLE_DURATION;

		//! DA; JP c,**: If condition cc is true, ** is copied to pc.
		case 0xDA:
			return JP(reg, reg.fc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! DC; CALL c,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		case 0xDC:
			return CALLC(cpu, reg, reg.fc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! DE; SBC a,*: Subtracts * and the carry flag from a.
		case 0xDE:
			return SUB8(reg, reg.a, cpu.fetchArgument(), reg.fc) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! DF; RST 18h: The current pc value plus one is pushed onto the stack, then is loaded with 18h.
		case 0xDF:
			return CALL(cpu, reg, 0x18);

		//! E0; LD (FF00+*),a: Load a to the address $FF00+*
		case 0xE0:
			return LD8toPTR(cpu, 0xFF00 + cpu.fetchArgument(), reg.a);

		//! E1; POP hl: The memory location pointed to by sp is stored into l and sp is incremented. The memory location pointed to by sp is stored into h and sp is incremented again.
		case 0xE1:
			return POP(cpu, reg, reg.hl);

		//! E2; LD (FF00+c),a: Load a to the address $FF00+c
		case 0xE2:
			return LD8toPTR(cpu, reg.c + 0xFF00, reg.a);

		//! E5; PUSH hl: sp is decremented and h is stored into the memory location pointed to by sp. sp is decremented again and l is stored into the memory location pointed to by sp.
		case 0xE5:
			return PUSH(cpu, reg, reg.hl);

		//! E6; AND *: Bitwise AND on a with *.
		case 0xE6:
			return AND8(reg, reg.a, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! E7; RST 20h: The current pc value plus one is pushed onto the stack, then is loaded with 20h.
		case 0xE7:
			return CALL(cpu, reg, 0x20);

		//! E8; ADD SP,*: Add the signed value * to sp.
		case 0xE8:
			return SPECIAL_ADD(reg, reg.sp, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! E9; JP (hl): Loads the value of hl into pc.
		case 0xE9:
			return JP(reg, true, reg.hl), JUMP_CYCLE_DURATION;

		//! EA; LD (**),a: Load a into the address pointed to by **
		case 0xEA:
			return LD8toPTR(cpu, cpu.fetchArgument16(), reg.a) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! EE; XOR *: Bitwise XOR on a with *.
		case 0xEE:
			return XOR(reg, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! EF; RST 28h: The current pc value plus one is pushed onto the stack, then is loaded with 28h.
		case 0xEF:
			return CALL(cpu, reg, 0x28);

		//! F0; LD a,(FF00+*): Load the value at address $FF00+* to a
		case 0xF0:
			return LD8fromPTR(cpu, reg.a, cpu.fetchArgument() + 0xFF00) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! F1; POP af: The memory location pointed to by sp is stored into f and sp is incremented. The memory location pointed to by sp is stored into a and sp is incremented again.
		case 0xF1:
			return POP(cpu, reg, reg.af);

		//! F2; LD a,(FF00+c): Load the value at address $FF00+c to a.
		case 0xF2:
			return LD8fromPTR(cpu, reg.a, 0xFF00 + reg.c);

		//! F3; DI: Resets both interrupt flip-flops, thus prenting maskable interrupts from triggering.
		case 0xF3:
			return cpu.setInterruptMaster(false), LD_CYCLE_DURATION;

		//! F5; PUSH af: sp is decremented and a is stored into the memory location pointed to by sp. sp is decremented again and f is stored into the memory location pointed to by sp.
		case 0xF5:
			return PUSH(cpu, reg, reg.af);

		//! F6; OR *: Bitwise OR on a with *.
		case 0xF6:
			return OR8(reg, reg.a, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! F7; RST 30h: The current pc value plus one is pushed onto the stack, then is loaded with 30h.
		case 0xF7:
			return CALL(cpu, reg, 0x30);

		//! F8; LD hl,sp+*: Load sp + the signed value * to hl.
		case 0xF8:
			return LD16(reg.hl, reg.sp), SPECIAL_ADD(reg, reg.hl, cpu.fetchArgument()), FETCH_ARGUMENT8_CYLCE_DURATION + LD_CYCLE_DURATION + ARITHMETIC_OPERATION_CYCLE_DURATION;

		//! F9; LD sp,hl: Loads the value of hl into sp.
		case 0xF9:
			return LD16(reg.sp, reg.hl);

		//! FA; LD a,(**): Load the value pointed to by address ** to a
		case 0xFA:
			return LD8fromPTR(cpu, reg.a, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION;

		//! FB; EI: Sets both interrupt flip-flops, thus allowing maskable interrupts to occur. An interrupt will not occur until after the immediatedly following instruction.
		case 0xFB:
			return cpu.setInterruptMaster(true), LD_CYCLE_DURATION;

		//! FE; CP *: Subtracts * from a and affects flags according to the result. a is not modified.
		case 0xFE:
			return CP(reg, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION;

		//! FF; RST 38h: The current pc value plus one is pushed onto the stack, then is loaded with 38h.
		case 0xFF:
			return CALL(cpu, reg, 0x38);

		default:
			throw GBEmulator::CPU::InvalidOpcodeException(opcode, cpu.getDecPc());
		}
	}

	const std::function<std::string(const CPU &, unsigned short)> _instructionsString[256] = {
			[](const CPU &, unsigned short) { return "NOP"; },
			[](const CPU &cpu, unsigned short address) {
				return "LD bc," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "LD (bc), a"; },
			[](const CPU &, unsigned short) { return "INC bc"; },
			[](const CPU &, unsigned short) { return "INC b"; },
			[](const CPU &, unsigned short) { return "DEC b"; },
			[](const CPU &cpu, unsigned short address) { return "LD b," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RLCA"; },
			[](const CPU &cpu, unsigned short address) {
				return "LD (" + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)) + "), SP";
			},
			[](const CPU &, unsigned short) { return "ADD hl,bc"; },
			[](const CPU &, unsigned short) { return "LD a,(bc)"; },
			[](const CPU &, unsigned short) { return "DEC bc"; },
			[](const CPU &, unsigned short) { return "INC c"; },
			[](const CPU &, unsigned short) { return "DEC c"; },
			[](const CPU &cpu, unsigned short address) { return "LD c," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RRCA"; },
			[](const CPU &, unsigned short) { return "STOP"; },
			[](const CPU &cpu, unsigned short address) {
				return "LD de," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "LD (de),a"; },
			[](const CPU &, unsigned short) { return "INC de"; },
			[](const CPU &, unsigned short) { return "INC d"; },
			[](const CPU &, unsigned short) { return "DEC d"; },
			[](const CPU &cpu, unsigned short address) { return "LD d," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RLA"; },
			[](const CPU &cpu, unsigned short address) { return "JR " + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "ADD hl,de"; },
			[](const CPU &, unsigned short) { return "LD a,(de)"; },
			[](const CPU &, unsigned short) { return "DEC de"; },
			[](const CPU &, unsigned short) { return "INC e"; },
			[](const CPU &, unsigned short) { return "DEC e"; },
			[](const CPU &cpu, unsigned short address) { return "LD e," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RRA"; },
			[](const CPU &cpu, unsigned short address) { return "JR nz," + intToHex(cpu.read(address)); },
			[](const CPU &cpu, unsigned short address) {
				return "LD hl, " + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "LDI (hl),a"; },
			[](const CPU &, unsigned short) { return "INC hl"; },
			[](const CPU &, unsigned short) { return "INC h"; },
			[](const CPU &, unsigned short) { return "DEC h"; },
			[](const CPU &cpu, unsigned short address) { return "LD h," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "DAA"; },
			[](const CPU &cpu, unsigned short address) { return "JR z," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "ADD hl,hl"; },
			[](const CPU &, unsigned short) { return "LDI a,(hl)"; },
			[](const CPU &, unsigned short) { return "DEC hl"; },
			[](const CPU &, unsigned short) { return "INC l"; },
			[](const CPU &, unsigned short) { return "DEC l"; },
			[](const CPU &cpu, unsigned short address) { return "LD l," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "CPL"; },
			[](const CPU &cpu, unsigned short address) { return "JR nc," + intToHex(cpu.read(address)); },
			[](const CPU &cpu, unsigned short address) {
				return "LD sp, " + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "LD (hl-), a"; },
			[](const CPU &, unsigned short) { return "INC sp"; },
			[](const CPU &, unsigned short) { return "INC (hl)"; },
			[](const CPU &, unsigned short) { return "DEC (hl)"; },
			[](const CPU &cpu, unsigned short address) { return "LD (hl)," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "SCF"; },
			[](const CPU &cpu, unsigned short address) { return "JR c," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "ADD hl,sp"; },
			[](const CPU &, unsigned short) { return "LDD a,(hl)"; },
			[](const CPU &, unsigned short) { return "DEC sp"; },
			[](const CPU &, unsigned short) { return "INC a"; },
			[](const CPU &, unsigned short) { return "DEC a"; },
			[](const CPU &cpu, unsigned short address) { return "LD a," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "CCF"; },
			[](const CPU &, unsigned short) { return "LD b,b"; },
			[](const CPU &, unsigned short) { return "LD b,c"; },
			[](const CPU &, unsigned short) { return "LD b,d"; },
			[](const CPU &, unsigned short) { return "LD b,e"; },
			[](const CPU &, unsigned short) { return "LD b,h"; },
			[](const CPU &, unsigned short) { return "LD b,l"; },
			[](const CPU &, unsigned short) { return "LD b,(hl)"; },
			[](const CPU &, unsigned short) { return "LD b,a"; },
			[](const CPU &, unsigned short) { return "LD c,b"; },
			[](const CPU &, unsigned short) { return "LD c,c"; },
			[](const CPU &, unsigned short) { return "LD c,d"; },
			[](const CPU &, unsigned short) { return "LD c,e"; },
			[](const CPU &, unsigned short) { return "LD c,h"; },
			[](const CPU &, unsigned short) { return "LD c,l"; },
			[](const CPU &, unsigned short) { return "LD c,(hl)"; },
			[](const CPU &, unsigned short) { return "LD c,a"; },
			[](const CPU &, unsigned short) { return "LD d,b"; },
			[](const CPU &, unsigned short) { return "LD d,c"; },
			[](const CPU &, unsigned short) { return "LD d,d"; },
			[](const CPU &, unsigned short) { return "LD d,e"; },
			[](const CPU &, unsigned short) { return "LD d,h"; },
			[](const CPU &, unsigned short) { return "LD d,l"; },
			[](const CPU &, unsigned short) { return "LD d,(hl)"; },
			[](const CPU &, unsigned short) { return "LD d,a"; },
			[](const CPU &, unsigned short) { return "LD e,b"; },
			[](const CPU &, unsigned short) { return "LD e,c"; },
			[](const CPU &, unsigned short) { return "LD e,d"; },
			[](const CPU &, unsigned short) { return "LD e,e"; },
			[](const CPU &, unsigned short) { return "LD e,h"; },
			[](const CPU &, unsigned short) { return "LD e,l"; },
			[](const CPU &, unsigned short) { return "LD e,(hl)"; },
			[](const CPU &, unsigned short) { return "LD e,a"; },
			[](const CPU &, unsigned short) { return "LD h,b"; },
			[](const CPU &, unsigned short) { return "LD h,c"; },
			[](const CPU &, unsigned short) { return "LD h,d"; },
			[](const CPU &, unsigned short) { return "LD h,e"; },
			[](const CPU &, unsigned short) { return "LD h,h"; },
			[](const CPU &, unsigned short) { return "LD h,l"; },
			[](const CPU &, unsigned short) { return "LD h,(hl)"; },
			[](const CPU &, unsigned short) { return "LD h,a"; },
			[](const CPU &, unsigned short) { return "LD l,b"; },
			[](const CPU &, unsigned short) { return "LD l,c"; },
			[](const CPU &, unsigned short) { return "LD l,d"; },
			[](const CPU &, unsigned short) { return "LD l,e"; },
			[](const CPU &, unsigned short) { return "LD l,h"; },
			[](const CPU &, unsigned short) { return "LD l,l"; },
			[](const CPU &, unsigned short) { return "LD l,(hl)"; },
			[](const CPU &, unsigned short) { return "LD l,a"; },
			[](const CPU &, unsigned short) { return "LD (hl),b"; },
			[](const CPU &, unsigned short) { return "LD (hl),c"; },
			[](const CPU &, unsigned short) { return "LD (hl),d"; },
			[](const CPU &, unsigned short) { return "LD (hl),e"; },
			[](const CPU &, unsigned short) { return "LD (hl),h"; },
			[](const CPU &, unsigned short) { return "LD (hl),l"; },
			[](const CPU &, unsigned short) { return "HALT"; },
			[](const CPU &, unsigned short) { return "LD (hl),a"; },
			[](const CPU &, unsigned short) { return "LD a,b"; },
			[](const CPU &, unsigned short) { return "LD a,c"; },
			[](const CPU &, unsigned short) { return "LD a,d"; },
			[](const CPU &, unsigned short) { return "LD a,e"; },
			[](const CPU &, unsigned short) { return "LD a,h"; },
			[](const CPU &, unsigned short) { return "LD a,l"; },
			[](const CPU &, unsigned short) { return "LD a,(hl)"; },
			[](const CPU &, unsigned short) { return "LD a,a"; },
			[](const CPU &, unsigned short) { return "ADD a,b"; },
			[](const CPU &, unsigned short) { return "ADD a,c"; },
			[](const CPU &, unsigned short) { return "ADD a,d"; },
			[](const CPU &, unsigned short) { return "ADD a,e"; },
			[](const CPU &, unsigned short) { return "ADD a,h"; },
			[](const CPU &, unsigned short) { return "ADD a,l"; },
			[](const CPU &, unsigned short) { return "ADD a,(hl)"; },
			[](const CPU &, unsigned short) { return "ADD a,a"; },
			[](const CPU &, unsigned short) { return "ADC a,b"; },
			[](const CPU &, unsigned short) { return "ADC a,c"; },
			[](const CPU &, unsigned short) { return "ADC a,d"; },
			[](const CPU &, unsigned short) { return "ADC a,e"; },
			[](const CPU &, unsigned short) { return "ADC a,h"; },
			[](const CPU &, unsigned short) { return "ADC a,l"; },
			[](const CPU &, unsigned short) { return "ADC a,(hl)"; },
			[](const CPU &, unsigned short) { return "ADC a,a"; },
			[](const CPU &, unsigned short) { return "SUB b"; },
			[](const CPU &, unsigned short) { return "SUB c"; },
			[](const CPU &, unsigned short) { return "SUB d"; },
			[](const CPU &, unsigned short) { return "SUB e"; },
			[](const CPU &, unsigned short) { return "SUB h"; },
			[](const CPU &, unsigned short) { return "SUB l"; },
			[](const CPU &, unsigned short) { return "SUB (hl)"; },
			[](const CPU &, unsigned short) { return "SUB a"; },
			[](const CPU &, unsigned short) { return "SBC a,b"; },
			[](const CPU &, unsigned short) { return "SBC a,c"; },
			[](const CPU &, unsigned short) { return "SBC a,d"; },
			[](const CPU &, unsigned short) { return "SBC a,e"; },
			[](const CPU &, unsigned short) { return "SBC a,h"; },
			[](const CPU &, unsigned short) { return "SBC a,l"; },
			[](const CPU &, unsigned short) { return "SBC a,(hl)"; },
			[](const CPU &, unsigned short) { return "SBC a,a"; },
			[](const CPU &, unsigned short) { return "AND b"; },
			[](const CPU &, unsigned short) { return "AND c"; },
			[](const CPU &, unsigned short) { return "AND d"; },
			[](const CPU &, unsigned short) { return "AND e"; },
			[](const CPU &, unsigned short) { return "AND h"; },
			[](const CPU &, unsigned short) { return "AND l"; },
			[](const CPU &, unsigned short) { return "AND (hl)"; },
			[](const CPU &, unsigned short) { return "AND a"; },
			[](const CPU &, unsigned short) { return "XOR b"; },
			[](const CPU &, unsigned short) { return "XOR c"; },
			[](const CPU &, unsigned short) { return "XOR d"; },
			[](const CPU &, unsigned short) { return "XOR e"; },
			[](const CPU &, unsigned short) { return "XOR h"; },
			[](const CPU &, unsigned short) { return "XOR l"; },
			[](const CPU &, unsigned short) { return "XOR (hl)"; },
			[](const CPU &, unsigned short) { return "XOR a"; },
			[](const CPU &, unsigned short) { return "OR b"; },
			[](const CPU &, unsigned short) { return "OR c"; },
			[](const CPU &, unsigned short) { return "OR d"; },
			[](const CPU &, unsigned short) { return "OR e"; },
			[](const CPU &, unsigned short) { return "OR h"; },
			[](const CPU &, unsigned short) { return "OR l"; },
			[](const CPU &, unsigned short) { return "OR (hl)"; },
			[](const CPU &, unsigned short) { return "OR a"; },
			[](const CPU &, unsigned short) { return "CP b"; },
			[](const CPU &, unsigned short) { return "CP c"; },
			[](const CPU &, unsigned short) { return "CP d"; },
			[](const CPU &, unsigned short) { return "CP e"; },
			[](const CPU &, unsigned short) { return "CP h"; },
			[](const CPU &, unsigned short) { return "CP l"; },
			[](const CPU &, unsigned short) { return "CP (hl)"; },
			[](const CPU &, unsigned short) { return "CP a"; },
			[](const CPU &, unsigned short) { return "RET nz"; },
			[](const CPU &, unsigned short) { return "POP bc"; },
			[](const CPU &cpu, unsigned short address) {
				return "JP nz," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &cpu, unsigned short address) {
				return "JP " + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &cpu, unsigned short address) {
				return "CALL nz," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "PUSH bc"; },
			[](const CPU &cpu, unsigned short address) { return "ADD a," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RST 00h"; },
			[](const CPU &, unsigned short) { return "RET z"; },
			[](const CPU &, unsigned short) { return "RET"; },
			[](const CPU &cpu, unsigned short address) {
				return "JP z," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &cpu, unsigned short address) {
				return _bitLevelInstructionsString[cpu.read(address)](cpu, address + 1);
			},
			[](const CPU &cpu, unsigned short address) {
				return "CALL z," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &cpu, unsigned short address) {
				return "CALL " + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &cpu, unsigned short address) { return "ADC a," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RST 08h"; },
			[](const CPU &, unsigned short) { return "RET nc"; },
			[](const CPU &, unsigned short) { return "POP de"; },
			[](const CPU &cpu, unsigned short address) {
				return "JP nc," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &cpu, unsigned short address) {
				return "CALL nc," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "PUSH de"; },
			[](const CPU &cpu, unsigned short address) { return "SUB " + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RST 10h"; },
			[](const CPU &, unsigned short) { return "RET c"; },
			[](const CPU &, unsigned short) { return "RETI"; },
			[](const CPU &cpu, unsigned short address) {
				return "JP c," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &cpu, unsigned short address) {
				return "CALL c," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address));
			},
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &cpu, unsigned short address) { return "SBC a," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RST 18h"; },
			[](const CPU &cpu, unsigned short address) { return "LD (FF00+" + intToHex(cpu.read(address)) + "),a"; },
			[](const CPU &, unsigned short) { return "POP hl"; },
			[](const CPU &, unsigned short) { return "LD (FF00+c),a"; },
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &, unsigned short) { return "PUSH hl"; },
			[](const CPU &cpu, unsigned short address) { return "AND " + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RST 20h"; },
			[](const CPU &cpu, unsigned short address) { return "ADD sp," + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "JP (hl)"; },
			[](const CPU &cpu, unsigned short address) {
				return "LD (" + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)) + "),a";
			},
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &cpu, unsigned short address) { return "XOR " + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RST 28h"; },
			[](const CPU &cpu, unsigned short address) { return "LD a,(FF00+" + intToHex(cpu.read(address)) + ")"; },
			[](const CPU &, unsigned short) { return "POP af"; },
			[](const CPU &, unsigned short) { return "LD a,(FF00+c)"; },
			[](const CPU &, unsigned short) { return "DI"; },
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &, unsigned short) { return "PUSH af"; },
			[](const CPU &cpu, unsigned short address) { return "OR " + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RST 30h"; },
			[](const CPU &cpu, unsigned short address) { return "LD hl,sp+" + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "LD sp,hl"; },
			[](const CPU &cpu, unsigned short address) {
				return "LD a,(" + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)) + ")";
			},
			[](const CPU &, unsigned short) { return "EI"; },
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &, unsigned short) { return "Invalid Opcode"; },
			[](const CPU &cpu, unsigned short address) { return "CP " + intToHex(cpu.read(address)); },
			[](const CPU &, unsigned short) { return "RST 38h"; },
	};
}