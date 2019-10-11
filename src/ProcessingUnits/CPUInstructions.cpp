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
	const std::map<unsigned char, std::function<unsigned char (CPU &, CPU::Registers &)>> _bitLevelInstructions{
		//! 7C; BIT 7,h
		{0x7C, [](CPU &, CPU::Registers &reg){ return BIT(reg, reg.h, 7); }},
	};

	const std::map<unsigned char, std::function<unsigned char (CPU &, CPU::Registers &)>> _instructions{
		//! 00; NOP: do nothing
		{0x00, [](CPU &, CPU::Registers &) { return NOP_CYCLE_DURATION; }},

		//! 01; LD bc,**: Loads ** into bc.
		{0x01, [](CPU &cpu, CPU::Registers &reg) { return LD16(reg.bc, cpu.fetchArgument16()); }},

		//! 02; LD (bc), a: Stores a into the memory location pointed to by bc
		{0x02, [](CPU &cpu, CPU::Registers &reg) { return LDPTR(cpu, reg.bc, reg.a); }},

		//! 03; INC bc: Adds one to bc.

		//! 04; INC b: Adds one to b.

		//! 05; DEC b: Subtracts one from b.

		//! 06; LD b,*: Loads * into b.
		{0x06, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.b, cpu.fetchArgument()); }},

		//! 07; RLCA: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and bit 0.

		//! 08; EX af,af': Exchanges the 16-bit contents of af and af'.

		//! 09; ADD hl,bc: The value of bc is added to hl.

		//! 0A; LD a,(bc): Loads the value pointed to by bc into a.

		//! 0B; DEC bc: Subtracts one from bc.

		//! 0C; INC c: Adds one to c.

		//! 0D; DEC c: Subtracts one from c.

		//! 0E; LD c,*: Loads * into c.
		{0x0E, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.c, cpu.fetchArgument()); }},

		//! 0F; RRCA: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and bit 7.

		//! 10; DJNZ *: The b register is decremented, and if not zero, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.

		//! 11; LD de,**: Loads ** into de.
		{0x11, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD16(reg.de, cpu.fetchArgument16()); }},

		//! 12; LD (de),a: Stores a into the memory location pointed to by de.
		{0x12, [](CPU &cpu, CPU::Registers &reg) { Instructions::LDPTR(cpu, reg.de, reg.a); }},

		//! 13; INC de: Adds one to de.

		//! 14; INC d: Adds one to d.

		//! 15; DEC d: Subtracts one from d.

		//! 16; LD d,*: Loads * into d.
		{0x16, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.d, cpu.fetchArgument()); }},

		//! 17; RLA: The contents of a are rotated left one bit position. The contents of bit 7 are copied to the carry flag and the previous contents of the carry flag are copied to bit 0.

		//! 18; JR *: The signed value * is added to pc. The jump is measured from the start of the instruction opcode.

		//! 19; ADD hl,de: The value of de is added to hl.

		//! 1A; LD a,(de): Loads the value pointed to by de into a.

		//! 1B; DEC de: Subtracts one from de.

		//! 1C; INC e: Adds one to e.

		//! 1D; DEC e: Subtracts one from e.

		//! 1E; LD e,*: Loads * into e.
		{0x1E, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.e, cpu.fetchArgument()); }},

		//! 1F; RRA: The contents of a are rotated right one bit position. The contents of bit 0 are copied to the carry flag and the previous contents of the carry flag are copied to bit 7.

		//! 20; JR nz,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.
		{0x20, [](CPU &cpu, CPU::Registers &reg) { return JR(reg, !reg.fz, cpu.fetchArgument()) + FETCH_ARGUMENT8_CYLCE_DURATION; }},

		//! 21; LD hl, **: Loads ** into hl register
		{0x21, [](CPU &cpu, CPU::Registers &reg) { return LD16(reg.hl, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; }},

		//! 22; LD (**),hl: Stores hl into the memory location pointed to by **.
		{0x22, [](CPU &cpu, CPU::Registers &reg) { Instructions::LDPTR(cpu, cpu.fetchArgument16(), reg.hl); }}, //TODO: reg.hl into uchar ??

		//! 23; INC hl: Adds one to hl.

		//! 24; INC h: Adds one to h.

		//! 25; DEC h: Subtracts one from h.

		//! 26; LD h,*: Loads * into h.
		{0x26, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.h, cpu.fetchArgument()); }},

		//! 27; DAA: Adjusts a for BCD addition and subtraction operations.

		//! 28; JR z,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.

		//! 29; ADD hl,hl: The value of hl is added to hl.

		//! 2A; LD hl,(**): Loads the value pointed to by ** into hl.

		//! 2B; DEC hl: Subtracts one from hl.

		//! 2C; INC l: Adds one to l.

		//! 2D; DEC l: Subtracts one from l.

		//! 2E; LD l,*: Loads * into l.

		//! 2F; CPL: The contents of a are inverted (one's complement).

		//! 30; JR nc,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.

		//! 31; LD sp, **: Loads ** into sp register
		{0x31, [](CPU &cpu, CPU::Registers &reg) { return LD16(reg.sp, cpu.fetchArgument16()) + FETCH_ARGUMENT16_CYLCE_DURATION; }},

		//! 32; LD (hl-), a: Loads a into address pointed to by hl and decrement hl
		{0x32, [](CPU &cpu, CPU::Registers &reg) { return LDPTR(cpu, reg.hl--, reg.a); }},

		//! 33; INC sp: Adds one to sp.

		//! 34; INC (hl): Adds one to (hl).

		//! 35; DEC (hl): Subtracts one from (hl).

		//! 36; LD (hl),*: Loads * into (hl).
		{0x36, [](CPU &cpu, CPU::Registers &reg) { Instructions::LDPTR(cpu, reg.hl, cpu.fetchArgument()); }},

		//! 37; SCF: Sets the carry flag.

		//! 38; JR c,*: If condition cc is true, the signed value * is added to pc. The jump is measured from the start of the instruction opcode.

		//! 39; ADD hl,sp: The value of hl is added to hl.

		//! 3A; LD a,(**): Loads the value pointed to by ** into a.

		//! 3B; DEC sp: Subtracts one from sp.

		//! 3C; INC a: Adds one to a.

		//! 3D; DEC a: Subtracts one from a.

		//! 3E; LD a,*: Loads * into a.
		{0x3E, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.a, cpu.fetchArgument()); }},

		//! 3F; CCF: Inverts the carry flag.

		//! 40; LD b,b: The contents of b are loaded into b.
		{0x40, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.b, reg.b); }},

		//! 41; LD b,c: The contents of c are loaded into b.
		{0x41, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.b, reg.c); }},

		//! 42; LD b,d: The contents of d are loaded into b.
		{0x42, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.b, reg.d); }},

		//! 43; LD b,e: The contents of e are loaded into b.
		{0x43, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.b, reg.e); }},

		//! 44; LD b,h: The contents of h are loaded into b.
		{0x44, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.b, reg.h); }},

		//! 45; LD b,l: The contents of l are loaded into b.
		{0x45, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.b, reg.l); }},

		//! 46; LD b,(hl): The contents of (hl) are loaded into b.

		//! 47; LD b,a: The contents of a are loaded into b.
		{0x47, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.b, reg.a); }},

		//! 48; LD c,b: The contents of b are loaded into c.
		{0x48, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.c, reg.b); }},

		//! 49; LD c,c: The contents of c are loaded into c.
		{0x49, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.c, reg.c); }},

		//! 4A; LD c,d: The contents of d are loaded into c.
		{0x4A, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.c, reg.d); }},

		//! 4B; LD c,e: The contents of e are loaded into c.
		{0x4B, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.c, reg.e); }},

		//! 4C; LD c,h: The contents of h are loaded into c.
		{0x4C, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.c, reg.h); }},

		//! 4D; LD c,l: The contents of l are loaded into c.
		{0x4D, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.c, reg.l); }},

		//! 4E; LD c,(hl): The contents of (hl) are loaded into c.

		//! 4F; LD c,a: The contents of a are loaded into c.
		{0x4F, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.c, reg.a); }},

		//! 50; LD d,b: The contents of b are loaded into d.
		{0x50, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.d, reg.b); }},

		//! 51; LD d,c: The contents of c are loaded into d.
		{0x51, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.d, reg.c); }},

		//! 52; LD d,d: The contents of d are loaded into d.
		{0x52, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.d, reg.d); }},

		//! 53; LD d,e: The contents of e are loaded into d.
		{0x53, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.d, reg.e); }},

		//! 54; LD d,h: The contents of h are loaded into d.
		{0x54, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.d, reg.h); }},

		//! 55; LD d,l: The contents of l are loaded into d.
		{0x55, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.d, reg.l); }},

		//! 56; LD d,(hl): The contents of (hl) are loaded into d.

		//! 57; LD d,a: The contents of a are loaded into d.
		{0x57, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.d, reg.a); }},

		//! 58; LD e,b: The contents of b are loaded into e.
		{0x58, [](CPU &cpu, CPU::Registers &reg) { Instructions::LD8(reg.e, reg.b); }},

		//! 59; LD e,c: The contents of c are loaded into e.

		//! 5A; LD e,d: The contents of d are loaded into e.

		//! 5B; LD e,e: The contents of e are loaded into e.

		//! 5C; LD e,h: The contents of h are loaded into e.

		//! 5D; LD e,l: The contents of l are loaded into e.

		//! 5E; LD e,(hl): The contents of (hl) are loaded into e.

		//! 5F; LD e,a: The contents of a are loaded into e.

		//! 60; LD h,b: The contents of b are loaded into h.

		//! 61; LD h,c: The contents of c are loaded into h.

		//! 62; LD h,d: The contents of d are loaded into h.

		//! 63; LD h,e: The contents of e are loaded into h.

		//! 64; LD h,h: The contents of h are loaded into h.

		//! 65; LD h,l: The contents of l are loaded into h.

		//! 66; LD h,(hl): The contents of (hl) are loaded into h.

		//! 67; LD h,a: The contents of a are loaded into h.

		//! 68; LD l,b: The contents of b are loaded into l.

		//! 69; LD l,c: The contents of c are loaded into l.

		//! 6A; LD l,d: The contents of d are loaded into l.

		//! 6B; LD l,e: The contents of e are loaded into l.

		//! 6C; LD l,h: The contents of h are loaded into l.

		//! 6D; LD l,l: The contents of l are loaded into l.

		//! 6E; LD l,(hl): The contents of (hl) are loaded into l.

		//! 6F; LD l,a: The contents of a are loaded into l.

		//! 70; LD (hl),b: The contents of b are loaded into (hl).

		//! 71; LD (hl),c: The contents of c are loaded into (hl).

		//! 72; LD (hl),d: The contents of d are loaded into (hl).

		//! 73; LD (hl),e: The contents of e are loaded into (hl).

		//! 74; LD (hl),h: The contents of h are loaded into (hl).

		//! 75; LD (hl),l: The contents of l are loaded into (hl).

		//! 76; HALT: Suspends CPU operation until an interrupt or reset occurs.

		//! 77; LD (hl),a: The contents of a are loaded into (hl).

		//! 78; LD a,b: The contents of b are loaded into a.

		//! 79; LD a,c: The contents of c are loaded into a.

		//! 7A; LD a,d: The contents of d are loaded into a.

		//! 7B; LD a,e: The contents of e are loaded into a.

		//! 7C; LD a,h: The contents of h are loaded into a.

		//! 7D; LD a,l: The contents of l are loaded into a.

		//! 7E; LD a,(hl): The contents of (hl) are loaded into a.

		//! 7F; LD a,a: The contents of a are loaded into a.

		//! 80; ADD a,b: Adds b to a.

		//! 81; ADD a,c: Adds c to a.

		//! 82; ADD a,d: Adds d to a.

		//! 83; ADD a,e: Adds e to a.

		//! 84; ADD a,h: Adds h to a.

		//! 85; ADD a,l: Adds l to a.

		//! 86; ADD a,(hl): Adds (hl) to a.

		//! 87; ADD a,a: Adds a to a.

		//! 88; ADC a,b: Adds b and the carry flag to a.

		//! 89; ADC a,c: Adds c and the carry flag to a.

		//! 8A; ADC a,d: Adds d and the carry flag to a.

		//! 8B; ADC a,e: Adds e and the carry flag to a.

		//! 8C; ADC a,h: Adds h and the carry flag to a.

		//! 8D; ADC a,l: Adds l and the carry flag to a.

		//! 8E; ADC a,(hl): Adds (hl) and the carry flag to a.

		//! 8F; ADC a,a: Adds a and the carry flag to a.

		//! 90; SUB b: Subtracts b from a.

		//! 91; SUB c: Subtracts c from a.

		//! 92; SUB d: Subtracts d from a.

		//! 93; SUB e: Subtracts e from a.

		//! 94; SUB h: Subtracts h from a.

		//! 95; SUB l: Subtracts l from a.

		//! 96; SUB (hl): Subtracts (hl) from a.

		//! 97; SUB a: Subtracts a from a.

		//! 98; SBC a,b: Subtracts b and the carry flag from a.

		//! 99; SBC a,c: Subtracts c and the carry flag from a.

		//! 9A; SBC a,d: Subtracts d and the carry flag from a.

		//! 9B; SBC a,e: Subtracts e and the carry flag from a.

		//! 9C; SBC a,h: Subtracts h and the carry flag from a.

		//! 9D; SBC a,l: Subtracts l and the carry flag from a.

		//! 9E; SBC a,(hl): Subtracts (hl) and the carry flag from a.

		//! 9F; SBC a,a: Subtracts a and the carry flag from a.

		//! A0; AND b: Bitwise AND on a with b.

		//! A1; AND c: Bitwise AND on a with c.

		//! A2; AND d: Bitwise AND on a with d.

		//! A3; AND e: Bitwise AND on a with e.

		//! A4; AND h: Bitwise AND on a with h.

		//! A5; AND l: Bitwise AND on a with l.

		//! A6; AND (hl): Bitwise AND on a with (hl).

		//! A7; AND a: Bitwise AND on a with a.

		//! A8; XOR b: Bitwise XOR on a with b.

		//! A9; XOR c: Bitwise XOR on a with c.

		//! AA; XOR d: Bitwise XOR on a with d.

		//! AB; XOR e: Bitwise XOR on a with e.

		//! AC; XOR h: Bitwise XOR on a with h.

		//! AD; XOR l: Bitwise XOR on a with l.

		//! AE; XOR (hl): Bitwise XOR on a with (hl).

		//! AF; XOR a: Bitwise XOR a with a
		{0xAF, [](CPU &cpu, CPU::Registers &reg) { return XOR(reg, reg.a, reg.a); }},

		//! B0; OR b: Bitwise OR on a with b.

		//! B1; OR c: Bitwise OR on a with c.

		//! B2; OR d: Bitwise OR on a with d.

		//! B3; OR e: Bitwise OR on a with e.

		//! B4; OR h: Bitwise OR on a with h.

		//! B5; OR l: Bitwise OR on a with l.

		//! B6; OR (hl): Bitwise OR on a with (hl).

		//! B7; OR a: Bitwise OR on a with a.

		//! B8; CP b: Subtracts b from a and affects flags according to the result. a is not modified.

		//! B9; CP c: Subtracts c from a and affects flags according to the result. a is not modified.

		//! BA; CP d: Subtracts d from a and affects flags according to the result. a is not modified.

		//! BB; CP e: Subtracts e from a and affects flags according to the result. a is not modified.

		//! BC; BITS: BITS

		//! BD; CP h: Subtracts h from a and affects flags according to the result. a is not modified.

		//! BE; CP l: Subtracts l from a and affects flags according to the result. a is not modified.

		//! BF; CP (hl): Subtracts (hl) from a and affects flags according to the result. a is not modified.

		//! C0; CP a: Subtracts a from a and affects flags according to the result. a is not modified.

		//! C1; RET nz: If condition cc is true, the top stack entry is popped into pc.

		//! C2; POP bc: The memory location pointed to by sp is stored into c and sp is incremented. The memory location pointed to by sp is stored into b and sp is incremented again.

		//! C3; JP nz,**: If condition cc is true, ** is copied to pc.

		//! C4; JP **: ** is copied to pc.

		//! C5; CALL nz,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.

		//! C6; PUSH bc: sp is decremented and b is stored into the memory location pointed to by sp. sp is decremented again and c is stored into the memory location pointed to by sp.

		//! C7; ADD a,*: Adds * to a.

		//! C8; RST 00h: The current pc value plus one is pushed onto the stack, then is loaded with 00h.

		//! C9; RET z: If condition cc is true, the top stack entry is popped into pc.

		//! CA; RET: The top stack entry is popped into pc.

		//! CB; Prefix for bit level instructions
		{0xCB, [](CPU &cpu, CPU::Registers &reg) {
			unsigned char opcode = cpu.read(reg.pc++);

			try {
				return Instructions::_bitLevelInstructions.at(opcode)(cpu, reg);
			} catch (std::out_of_range &) {
				throw CPU::InvalidOpcodeException(0xCB00U | opcode, reg.pc - 2);
			}
		}},

		//! CC; CALL z,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.

		//! CD; CALL **: The current pc value plus three is pushed onto the stack, then is loaded with **.

		//! CE; ADC a,*: Adds * and the carry flag to a.

		//! CF; RST 08h: The current pc value plus one is pushed onto the stack, then is loaded with 08h.

		//! D0; RET nc: If condition cc is true, the top stack entry is popped into pc.

		//! D1; POP de: The memory location pointed to by sp is stored into e and sp is incremented. The memory location pointed to by sp is stored into d and sp is incremented again.

		//! D2; JP nc,**: If condition cc is true, ** is copied to pc.

		//! D3; OUT (*),a: The value of a is written to port *.

		//! D4; CALL nc,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.

		//! D5; PUSH de: sp is decremented and d is stored into the memory location pointed to by sp. sp is decremented again and e is stored into the memory location pointed to by sp.

		//! D6; SUB *: Subtracts * from a.

		//! D7; RST 10h: The current pc value plus one is pushed onto the stack, then is loaded with 10h.

		//! D8; RET c: If condition cc is true, the top stack entry is popped into pc.

		//! D9; EXX: Exchanges the 16-bit contents of bc, de, and hl with bc', de', and hl'.

		//! DA; JP c,**: If condition cc is true, ** is copied to pc.

		//! DB; IN a,(*): A byte from port * is written to a.

		//! DC; CALL c,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.

		//! DD; IX: IX

		//! DE; SBC a,*: Subtracts * and the carry flag from a.

		//! DF; RST 18h: The current pc value plus one is pushed onto the stack, then is loaded with 18h.

		//! E0; RET po: If condition cc is true, the top stack entry is popped into pc.

		//! E1; POP hl: The memory location pointed to by sp is stored into l and sp is incremented. The memory location pointed to by sp is stored into h and sp is incremented again.

		//! E2; JP po,**: If condition cc is true, ** is copied to pc.

		//! E3; EX (sp),hl: Exchanges (sp) with l, and (sp+1) with h.

		//! E4; CALL po,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.

		//! E5; PUSH hl: sp is decremented and h is stored into the memory location pointed to by sp. sp is decremented again and l is stored into the memory location pointed to by sp.

		//! E6; AND *: Bitwise AND on a with *.

		//! E7; RST 20h: The current pc value plus one is pushed onto the stack, then is loaded with 20h.

		//! E8; RET pe: If condition cc is true, the top stack entry is popped into pc.

		//! E9; JP (hl): Loads the value of hl into pc.

		//! EA; JP pe,**: If condition cc is true, ** is copied to pc.

		//! EB; EX de,hl: Exchanges the 16-bit contents of de and hl.

		//! EC; CALL pe,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.

		//! ED; EXTD: EXTD

		//! EE; XOR *: Bitwise XOR on a with *.

		//! EF; RST 28h: The current pc value plus one is pushed onto the stack, then is loaded with 28h.

		//! F0; RET p: If condition cc is true, the top stack entry is popped into pc.

		//! F1; POP af: The memory location pointed to by sp is stored into f and sp is incremented. The memory location pointed to by sp is stored into a and sp is incremented again.

		//! F2; JP p,**: If condition cc is true, ** is copied to pc.

		//! F3; DI: Resets both interrupt flip-flops, thus prenting maskable interrupts from triggering.

		//! F4; CALL p,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.

		//! F5; PUSH af: sp is decremented and a is stored into the memory location pointed to by sp. sp is decremented again and f is stored into the memory location pointed to by sp.

		//! F6; OR *: Bitwise OR on a with *.

		//! F7; RST 30h: The current pc value plus one is pushed onto the stack, then is loaded with 30h.

		//! F8; RET m: If condition cc is true, the top stack entry is popped into pc.

		//! F9; LD sp,hl: Loads the value of hl into sp.

		//! FA; JP m,**: If condition cc is true, ** is copied to pc.

		//! FB; EI: Sets both interrupt flip-flops, thus allowing maskable interrupts to occur. An interrupt will not occur until after the immediatedly following instruction.

		//! FC; CALL m,**: If condition cc is true, the current pc value plus three is pushed onto the stack, then is loaded with **.

		//! FD; IV: IV

		//! FE; CP *: Subtracts * from a and affects flags according to the result. a is not modified.

		//! FF; RST 38h: The current pc value plus one is pushed onto the stack, then is loaded with 38h.

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

	unsigned char JR(CPU::Registers &reg, bool cond, char off)
	{
		if (!cond)
			return BASIC_BIT_OPERATION_CYCLE_DURATION;
		reg.pc += off;
		return BASIC_BIT_OPERATION_CYCLE_DURATION + JUMP_CYCLE_DURATION;
	}

	unsigned char BIT(CPU::Registers &reg, unsigned char value, unsigned char bit)
	{
		setFlags(reg, ((1U << bit) & value) == 0 ? SET : UNSET, UNSET, SET, UNCHANGED);
		return COMPLEX_BIT_OPERATION_CYCLE_DURATION;
	}

	unsigned char XOR(CPU::Registers &reg, unsigned char &value1, unsigned char value2)
	{
		value1 ^= value2;
		setFlags(reg, value1 == 0 ? SET : UNSET, UNSET, UNSET, UNSET);
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

	unsigned char LDPTR(CPU &cpu, unsigned short address, unsigned char value)
	{
		cpu.write(address, value);
		return LD_CYCLE_DURATION + INDIRECTION_CYLCE_DURATION;
	}
}