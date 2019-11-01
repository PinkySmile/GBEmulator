/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Memory.hpp
*/

#ifndef GBEMULATOR_MEMORY_HPP
#define GBEMULATOR_MEMORY_HPP


#include <vector>

namespace GBEmulator::Memory
{
	class Memory {
	private:
		bool _readOnly;
		unsigned char _currentBank;
		unsigned short _bankSize;

	protected:
		size_t _size;
		unsigned char *_memory;

	public:
		Memory() = delete;
		Memory(const Memory &) = delete;
		~Memory();
		Memory &operator=(const Memory &) = delete;
		Memory(unsigned size, unsigned short bankSize, bool readOnly = false);

		void resize(size_t size, unsigned char fill = 0xFF);
		void setBank(unsigned char bank);
		void setBankSize(size_t size);
		unsigned char getCurrentBank() const;
		unsigned char read(unsigned short address) const;
		unsigned char rawRead(unsigned short address) const;
		size_t getSize() const;
		void setMemory(unsigned char *memory, size_t size);
		void write(unsigned short address,unsigned char value);
		void forceWrite(unsigned short address,unsigned char value);
		void dump(unsigned short offset = 0) const;
	};
}


#endif //GBEMULATOR_MEMORY_HPP
