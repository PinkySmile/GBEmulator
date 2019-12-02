/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** BasicInstructions.cpp
*/

#include "CPUInstructions.hpp"

namespace GBEmulator::Instructions
{
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
		[](CPU &, CPU::Registers &reg) { return RLCA(reg); },

		//! 08; LD (**), SP: Load the value pointed to by ** to sp
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
		[](CPU &, CPU::Registers &reg) { return RRCA(reg); },

		//! 10; STOP: Halts the CPU until a key is pressed
		[](CPU &cpu, CPU::Registers &) { return STOP(cpu); },

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
		[](CPU &, CPU::Registers &reg){ return RLA(reg); },

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
		[](CPU &, CPU::Registers &reg) { return RRA(reg); },

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
		[](CPU &, CPU::Registers &reg) { return DAA(reg, reg.a); },

		//! 28; JR z,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		[](CPU &cpu, CPU::Registers &reg) { return JR(reg, reg.fz, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 29; ADD hl,hl: The value of hl is added to hl.
		[](CPU &, CPU::Registers &reg) { return ADD16(reg, reg.hl, reg.hl); },

		//! 2A; LDI a,(hl): Loads the value pointed to by hl to a and increments hl
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, reg.hl++); },

		//! 2B; DEC hl: Subtracts one from hl.
		[](CPU &, CPU::Registers &reg) { return DEC16(reg.hl); },

		//! 2C; INC l: Adds one to l.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.l); },

		//! 2D; DEC l: Subtracts one from l.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.l); },

		//! 2E; LD l,*: Loads * into l.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.l, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 2F; CPL: The contents of a are inverted (one's complement).
		[](CPU &, CPU::Registers &reg) { return CPL(reg); },

		//! 30; JR nc,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		[](CPU &cpu, CPU::Registers &reg) { return JR(reg, !reg.fc, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

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
		[](CPU &, CPU::Registers &reg) { return setFlags(reg, UNCHANGED, UNSET, UNSET, SET), BASIC_BIT_OPERATION_CYCLE_DURATION; },

		//! 38; JR c,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		[](CPU &cpu, CPU::Registers &reg) { return JR(reg, reg.fc, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 39; ADD hl,sp: The value of sp is added to hl.
		[](CPU &, CPU::Registers &reg) { return ADD16(reg, reg.hl, reg.sp); },

		//! 3A; LDD a,(hl): Load the value pointed to by hl to a and decrements hl
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, reg.hl--) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! 3B; DEC sp: Subtracts one from sp.
		[](CPU &, CPU::Registers &reg) { return DEC16(reg.sp); },

		//! 3C; INC a: Adds one to a.
		[](CPU &, CPU::Registers &reg) { return INC8(reg, reg.a); },

		//! 3D; DEC a: Subtracts one from a.
		[](CPU &, CPU::Registers &reg) { return DEC8(reg, reg.a); },

		//! 3E; LD a,*: Loads * into a.
		[](CPU &cpu, CPU::Registers &reg) { return LD8(reg.a, cpu.fetchArgument()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! 3F; CCF: Inverts the carry flag.
		[](CPU &, CPU::Registers &reg) { return setFlags(reg, UNCHANGED, UNSET, UNSET, reg.fc ? UNSET : SET), BASIC_BIT_OPERATION_CYCLE_DURATION; },

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
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.b, false); },

		//! 81; ADD a,c: Adds c to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.c, false); },

		//! 82; ADD a,d: Adds d to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.d, false); },

		//! 83; ADD a,e: Adds e to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.e, false); },

		//! 84; ADD a,h: Adds h to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.h, false); },

		//! 85; ADD a,l: Adds l to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.l, false); },

		//! 86; ADD a,(hl): Adds (hl) to a.
		[](CPU &cpu, CPU::Registers &reg) { return ADD8(reg, reg.a, cpu.read(reg.hl), false) + INDIRECTION_CYCLE_DURATION; },

		//! 87; ADD a,a: Adds a to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.a, false); },

		//! 88; ADC a,b: Adds b and the carry flag to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.b, reg.fc); },

		//! 89; ADC a,c: Adds c and the carry flag to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.c, reg.fc); },

		//! 8A; ADC a,d: Adds d and the carry flag to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.d, reg.fc); },

		//! 8B; ADC a,e: Adds e and the carry flag to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.e, reg.fc); },

		//! 8C; ADC a,h: Adds h and the carry flag to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.h, reg.fc); },

		//! 8D; ADC a,l: Adds l and the carry flag to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.l, reg.fc); },

		//! 8E; ADC a,(hl): Adds (hl) and the carry flag to a.
		[](CPU &cpu, CPU::Registers &reg) { return ADD8(reg, reg.a, cpu.read(reg.hl), reg.fc) + INDIRECTION_CYCLE_DURATION; },

		//! 8F; ADC a,a: Adds a and the carry flag to a.
		[](CPU &, CPU::Registers &reg) { return ADD8(reg, reg.a, reg.a, reg.fc); },

		//! 90; SUB b: Subtracts b from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.b, false); },

		//! 91; SUB c: Subtracts c from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.c, false); },

		//! 92; SUB d: Subtracts d from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.d, false); },

		//! 93; SUB e: Subtracts e from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.e, false); },

		//! 94; SUB h: Subtracts h from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.h, false); },

		//! 95; SUB l: Subtracts l from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.l, false); },

		//! 96; SUB (hl): Subtracts (hl) from a.
		[](CPU &cpu, CPU::Registers &reg) { return SUB8(reg, reg.a, cpu.read(reg.hl), false) + INDIRECTION_CYCLE_DURATION; },

		//! 97; SUB a: Subtracts a from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.a, false); },

		//! 98; SBC a,b: Subtracts b and the carry flag from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.b, reg.fc); },

		//! 99; SBC a,c: Subtracts c and the carry flag from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.c, reg.fc); },

		//! 9A; SBC a,d: Subtracts d and the carry flag from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.d, reg.fc); },

		//! 9B; SBC a,e: Subtracts e and the carry flag from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.e, reg.fc); },

		//! 9C; SBC a,h: Subtracts h and the carry flag from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.h, reg.fc); },

		//! 9D; SBC a,l: Subtracts l and the carry flag from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.l, reg.fc); },

		//! 9E; SBC a,(hl): Subtracts (hl) and the carry flag from a.
		[](CPU &cpu, CPU::Registers &reg) { return SUB8(reg, reg.a, cpu.read(reg.hl), reg.fc) + INDIRECTION_CYCLE_DURATION; },

		//! 9F; SBC a,a: Subtracts a and the carry flag from a.
		[](CPU &, CPU::Registers &reg) { return SUB8(reg, reg.a, reg.a, reg.fc); },

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
		[](CPU &cpu, CPU::Registers &reg) { return AND8(reg, reg.a, cpu.read(reg.hl)) + INDIRECTION_CYCLE_DURATION; },

		//! A7; AND a: Bitwise AND on a with a.
		[](CPU &, CPU::Registers &reg) { return AND8(reg, reg.a, reg.a); },

		//! A8; XOR b: Bitwise XOR on a with b.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.b); },

		//! A9; XOR c: Bitwise XOR on a with c.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.c); },

		//! AA; XOR d: Bitwise XOR on a with d.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.d); },

		//! AB; XOR e: Bitwise XOR on a with e.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.e); },

		//! AC; XOR h: Bitwise XOR on a with h.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.h); },

		//! AD; XOR l: Bitwise XOR on a with l.
		[](CPU &, CPU::Registers &reg) { return XOR(reg, reg.l); },

		//! AE; XOR (hl): Bitwise XOR on a with (hl).
		[](CPU &cpu, CPU::Registers &reg) { return XOR(reg, cpu.read(reg.hl)) + INDIRECTION_CYCLE_DURATION; },

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
		[](CPU &cpu, CPU::Registers &reg) { return OR8(reg, reg.a, cpu.read(reg.hl)) + INDIRECTION_CYCLE_DURATION; },

		//! B7; OR a: Bitwise OR on a with a.
		[](CPU &, CPU::Registers &reg) { return OR8(reg, reg.a, reg.a); },

		//! B8; CP b: Subtracts b from a and affects flags according to the result. a is not modified.
		[](CPU &, CPU::Registers &reg) { return CP(reg, reg.b); },

		//! B9; CP c: Subtracts c from a and affects flags according to the result. a is not modified.
		[](CPU &, CPU::Registers &reg) { return CP(reg, reg.c); },

		//! BA; CP d: Subtracts d from a and affects flags according to the result. a is not modified.
		[](CPU &, CPU::Registers &reg) { return CP(reg, reg.d); },

		//! BB; CP e: Subtracts e from a and affects flags according to the result. a is not modified.
		[](CPU &, CPU::Registers &reg) { return CP(reg, reg.e); },

		//! BC; CP h: Subtracts h from a and affects flags according to the result. a is not modified.
		[](CPU &, CPU::Registers &reg) { return CP(reg, reg.h); },

		//! BD; CP l: Subtracts l from a and affects flags according to the result. a is not modified.
		[](CPU &, CPU::Registers &reg) { return CP(reg, reg.l); },

		//! BE; CP (hl): Subtracts (hl) from a and affects flags according to the result. a is not modified.
		[](CPU &cpu, CPU::Registers &reg) { return CP(reg, cpu.read(reg.hl)) + INDIRECTION_CYCLE_DURATION; },

		//! BF; CP a: Subtracts a from a and affects flags according to the result. a is not modified.
		[](CPU &, CPU::Registers &reg) { return CP(reg, reg.a); },

		//! C0; RET nz: If condition cc is true, the top stack entry is popped into pc.
		[](CPU &cpu, CPU::Registers &reg) { return RET(cpu, reg, !reg.fz); },

		//! C1; POP bc: The memory location pointed to by sp is stored into c and sp is incremented. The memory location pointed to by sp is stored into b and sp is incremented again.
		[](CPU &cpu, CPU::Registers &reg){ return POP(cpu, reg, reg.bc); },

		//! C2; JP nz,**: If condition cc is true, ** is copied to pc.
		[](CPU &cpu, CPU::Registers &reg) { return JP(reg, !reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! C3; JP **: ** is copied to pc.
		[](CPU &cpu, CPU::Registers &reg) { return JP(reg, true, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! C4; CALL nz,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		[](CPU &cpu, CPU::Registers &reg) { return CALLC(cpu, reg, !reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! C5; PUSH bc: sp is decremented and b is stored into the memory location pointed to by sp. sp is decremented again and c is stored into the memory location pointed to by sp.
		[](CPU &cpu, CPU::Registers &reg) { return PUSH(cpu, reg, reg.bc); },

		//! C6; ADD a,*: Adds * to a.
		[](CPU &cpu, CPU::Registers &reg) { return ADD8(reg, reg.a, cpu.fetchArgument(), false) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! C7; RST 00h: The current pc value plus one is pushed onto the stack, then is loaded with 00h.
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, 0x00); },

		//! C8; RET z: If condition cc is true, the top stack entry is popped into pc.
		[](CPU &cpu, CPU::Registers &reg) { return RET(cpu, reg, reg.fz); },

		//! C9; RET: The top stack entry is popped into pc.
		[](CPU &cpu, CPU::Registers &reg) { return POP(cpu, reg, reg.pc) + BASIC_BIT_OPERATION_CYCLE_DURATION; },

		//! CA; JP z,**: If condition cc is true, ** is copied to pc.
		[](CPU &cpu, CPU::Registers &reg) { return JP(reg, reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! CB; Prefix for bit level instructions
		[](CPU &cpu, CPU::Registers &reg) { return Instructions::_bitLevelInstructions[cpu.fetchArgument()](cpu, reg) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! CC; CALL z,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		[](CPU &cpu, CPU::Registers &reg) { return CALLC(cpu, reg, reg.fz, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! CD; CALL **: The current pc value plus three is pushed onto the stack, then is loaded with **.
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! CE; ADC a,*: Adds * and the carry flag to a.
		[](CPU &cpu, CPU::Registers &reg) { return ADD8(reg, reg.a, cpu.fetchArgument(), reg.fc) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! CF; RST 08h: The current pc value plus one is pushed onto the stack, then is loaded with 08h.
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, 0x08); },

		//! D0; RET nc: If condition cc is true, the top stack entry is popped into pc.
		[](CPU &cpu, CPU::Registers &reg) { return RET(cpu, reg, !reg.fc); },

		//! D1; POP de: The memory location pointed to by sp is stored into e and sp is incremented. The memory location pointed to by sp is stored into d and sp is incremented again.
		[](CPU &cpu, CPU::Registers &reg) { return POP(cpu, reg, reg.de); },

		//! D2; JP nc,**: If condition cc is true, ** is copied to pc.
		[](CPU &cpu, CPU::Registers &reg) { return JP(reg, !reg.fc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! D3; UNUSED
		{},

		//! D4; CALL nc,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		[](CPU &cpu, CPU::Registers &reg) { return CALLC(cpu, reg, !reg.fc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! D5; PUSH de: sp is decremented and d is stored into the memory location pointed to by sp. sp is decremented again and e is stored into the memory location pointed to by sp.
		[](CPU &cpu, CPU::Registers &reg) { return PUSH(cpu, reg, reg.de); },

		//! D6; SUB *: Subtracts * from a.
		[](CPU &cpu, CPU::Registers &reg) { return SUB8(reg, reg.a, cpu.fetchArgument(), false) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! D7; RST 10h: The current pc value plus one is pushed onto the stack, then is loaded with 10h.
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, 0x10); },

		//! D8; RET c: If condition cc is true, the top stack entry is popped into pc.
		[](CPU &cpu, CPU::Registers &reg) { return RET(cpu, reg, reg.fc); },

		//! D9; RETI
		[](CPU &cpu, CPU::Registers &reg) { return cpu.setInterruptMaster(true), POP(cpu, reg, reg.pc) + BASIC_BIT_OPERATION_CYCLE_DURATION; },

		//! DA; JP c,**: If condition cc is true, ** is copied to pc.
		[](CPU &cpu, CPU::Registers &reg) { return JP(reg, reg.fc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! DB; UNUSED
		{},

		//! DC; CALL c,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.
		[](CPU &cpu, CPU::Registers &reg) { return CALLC(cpu, reg, reg.fc, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; },

		//! DD; UNUSED
		{},

		//! DE; SBC a,*: Subtracts * and the carry flag from a.
		[](CPU &cpu, CPU::Registers &reg) { return SUB8(reg, reg.a, cpu.fetchArgument(), reg.fc) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! DF; RST 18h: The current pc value plus one is pushed onto the stack, then is loaded with 18h.
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, 0x18); },

		//! E0; LD (FF00+*),a: Load a to the address $FF00+*
		[](CPU &cpu, CPU::Registers &reg) { return LD8toPTR(cpu, 0xFF00 + cpu.fetchArgument(), reg.a); },

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
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, 0x20); },

		//! E8; ADD SP,*: Add the signed value * to sp.
		[](CPU &cpu, CPU::Registers &reg) { return SPECIAL_ADD(reg, reg.sp, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! E9; JP (hl): Loads the value of hl into pc.
		[](CPU &, CPU::Registers &reg) { return JP(reg, true, reg.hl), JUMP_CYCLE_DURATION; },

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
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, 0x28); },

		//! F0; LD a,(FF00+*): Load the value at address $FF00+* to a
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, cpu.fetchArgument() + 0xFF00) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! F1; POP af: The memory location pointed to by sp is stored into f and sp is incremented. The memory location pointed to by sp is stored into a and sp is incremented again.
		[](CPU &cpu, CPU::Registers &reg) { return POP(cpu, reg, reg.af); },

		//! F2; LD a,(FF00+c): Load the value at address $FF00+c to a.
		[](CPU &cpu, CPU::Registers &reg) { return LD8fromPTR(cpu, reg.a, 0xFF00 + reg.c); },

		//! F3; DI: Resets both interrupt flip-flops, thus prenting maskable interrupts from triggering.
		[](CPU &cpu, CPU::Registers &) { return cpu.setInterruptMaster(false), LD_CYCLE_DURATION; },

		//! F4; UNUSED
		{},

		//! F5; PUSH af: sp is decremented and a is stored into the memory location pointed to by sp. sp is decremented again and f is stored into the memory location pointed to by sp.
		[](CPU &cpu, CPU::Registers &reg) { return PUSH(cpu, reg, reg.af); },

		//! F6; OR *: Bitwise OR on a with *.
		[](CPU &cpu, CPU::Registers &reg) { return OR8(reg, reg.a, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; },

		//! F7; RST 30h: The current pc value plus one is pushed onto the stack, then is loaded with 30h.
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, 0x30); },

		//! F8; LD hl,sp+*: Load sp + the signed value * to hl.
		[](CPU &cpu, CPU::Registers &reg) { return LD16(reg.hl, reg.sp + static_cast<char>(cpu.fetchArgument())) + FETCH_ARGUMENT8_CYLCE_DURATION; },

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
		[](CPU &cpu, CPU::Registers &reg) { return CALL(cpu, reg, 0x38); }
	};

	const std::function<std::string (const CPU &, unsigned short)> _instructionsString[256] = {
		[](const CPU &, unsigned short) { return "NOP"; },
		[](const CPU &cpu, unsigned short address) { return "LD bc," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "LD (bc), a"; },
		[](const CPU &, unsigned short) { return "INC bc"; },
		[](const CPU &, unsigned short) { return "INC b"; },
		[](const CPU &, unsigned short) { return "DEC b"; },
		[](const CPU &cpu, unsigned short address) { return "LD b," + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "RLCA"; },
		[](const CPU &cpu, unsigned short address) { return "LD (" + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)) + "), SP"; },
		[](const CPU &, unsigned short) { return "ADD hl,bc"; },
		[](const CPU &, unsigned short) { return "LD a,(bc)"; },
		[](const CPU &, unsigned short) { return "DEC bc"; },
		[](const CPU &, unsigned short) { return "INC c"; },
		[](const CPU &, unsigned short) { return "DEC c"; },
		[](const CPU &cpu, unsigned short address) { return "LD c," + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "RRCA"; },
		[](const CPU &, unsigned short) { return "STOP"; },
		[](const CPU &cpu, unsigned short address) { return "LD de," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
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
		[](const CPU &cpu, unsigned short address) { return "LD hl, " + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
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
		[](const CPU &cpu, unsigned short address) { return "LD sp, " + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
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
		[](const CPU &cpu, unsigned short address) { return "JP nz," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &cpu, unsigned short address) { return "JP " + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &cpu, unsigned short address) { return "CALL nz," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "PUSH bc"; },
		[](const CPU &cpu, unsigned short address) { return "ADD a," + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "RST 00h"; },
		[](const CPU &, unsigned short) { return "RET z"; },
		[](const CPU &, unsigned short) { return "RET"; },
		[](const CPU &cpu, unsigned short address) { return "JP z," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &cpu, unsigned short address) { return _bitLevelInstructionsString[cpu.read(address)](cpu, address + 1); },
		[](const CPU &cpu, unsigned short address) { return "CALL z," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &cpu, unsigned short address) { return "CALL " + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &cpu, unsigned short address) { return "ADC a," + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "RST 08h"; },
		[](const CPU &, unsigned short) { return "RET nc"; },
		[](const CPU &, unsigned short) { return "POP de"; },
		[](const CPU &cpu, unsigned short address) { return "JP nc," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "Invalid Opcode"; },
		[](const CPU &cpu, unsigned short address) { return "CALL nc," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "PUSH de"; },
		[](const CPU &cpu, unsigned short address) { return "SUB " + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "RST 10h"; },
		[](const CPU &, unsigned short) { return "RET c"; },
		[](const CPU &, unsigned short) { return "RETI"; },
		[](const CPU &cpu, unsigned short address) { return "JP c," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "Invalid Opcode"; },
		[](const CPU &cpu, unsigned short address) { return "CALL c," + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)); },
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
		[](const CPU &cpu, unsigned short address) { return "LD (" + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)) + "),a"; },
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
		[](const CPU &cpu, unsigned short address) { return "LD a,(" + intToHex(cpu.read(address + 1)) + intToHex(cpu.read(address)) + ")"; },
		[](const CPU &, unsigned short) { return "EI"; },
		[](const CPU &, unsigned short) { return "Invalid Opcode"; },
		[](const CPU &, unsigned short) { return "Invalid Opcode"; },
		[](const CPU &cpu, unsigned short address) { return "CP " + intToHex(cpu.read(address)); },
		[](const CPU &, unsigned short) { return "RST 38h"; },
	};
}