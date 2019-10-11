/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.cpp
*/

#include "APU.hpp"

namespace GBEmulator
{
    APU::APU() :
    _memory(0x2F, 0x2F)
    {

    }

    void APU::write(unsigned short address, unsigned char value)
    {
        this->_memory.write(address, value);
    }

    unsigned char APU::read(unsigned short address) const
    {
        return this->_memory.read(address);
    }

    APU::~APU() = default;
}