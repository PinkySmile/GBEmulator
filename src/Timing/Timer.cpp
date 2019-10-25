/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Timer.cpp
*/

#include "Timer.hpp"

namespace GBEmulator::Timing
{
	Timer::Timer() :
		_expected(getCyclesPerSecondsFromFrequency(this->getFrequency()))
	{}

	double getCyclesPerSecondsFromFrequency(unsigned char frequency)
	{
		return GB_CPU_FREQUENCY / frequency;
	}

	unsigned char Timer::getControlByte() const
	{
		return this->_byte;
	}

	void Timer::setControlByte(unsigned char byte)
	{
		this->_byte = byte;
		this->_expected = getCyclesPerSecondsFromFrequency(this->getFrequency());
	}

	unsigned char Timer::getCounter() const
	{
		return this->_counter;
	}

	unsigned Timer::getFrequency() const
	{
		switch (this->_byte & 0b11U) {
		case 0b00:
			return 4096;
		case 0b01:
			return 262144;
		case 0b10:
			return 65536;
		default:
			return 16384;
		}
	}

	bool Timer::isActivated() const
	{
		return this->_byte & 0b100U;
	}

	void Timer::setCounter(unsigned char byte)
	{
		this->_counter = byte;
	}

	bool Timer::update(unsigned cycles)
	{
		if (!this->isActivated())
			return false;

		this->_cycles += cycles;
		if (this->_cycles > this->_expected) {
			this->_cycles -= this->_expected;
			if (!++this->_counter) {
				this->_counter = this->modulo;
				return true;
			}
		}
		return false;
	}
}
