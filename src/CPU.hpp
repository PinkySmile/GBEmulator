/*
** EPITECH PROJECT, 2022
** GBEmulator
** File description:
** Created by agrellier,
*/

#ifndef GBEMULATOR_CPU_HPP
#define GBEMULATOR_CPU_HPP

struct Registers {
	union {
		struct {
			unsigned char a;
			unsigned char f;
		};
		unsigned short af;
	};
	union {
		struct {
			unsigned char b;
			unsigned char c;
		};
		unsigned short bc;
	};
	union {
		struct {
			unsigned char d;
			unsigned char e;
		};
		unsigned short de;
	};
	union {
		struct {
			unsigned char h;
			unsigned char l;
		};
		unsigned short hl;
	};
	unsigned short pc;
	unsigned short sp;
};

class CPU {
};

#endif //GBEMULATOR_CPU_HPP
