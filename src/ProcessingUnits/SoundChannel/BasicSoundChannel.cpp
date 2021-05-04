//
// Created by andgel on 04/05/2021
//

#include "BasicSoundChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator
{
	void BasicSoundChannel::write(unsigned int relativeAddress, unsigned char value)
	{

	}

	unsigned char BasicSoundChannel::read(unsigned int relativeAddress)
	{
		return 0xFF;
	}

	std::vector<short> BasicSoundChannel::update(unsigned int cycles)
	{
		this->_update(cycles);
		this->_cycles += cycles;
		if (this->_cycles >= GB_CPU_FREQUENCY / 44100.) {
			auto data = this->_getSoundData();

			this->_cycles -= GB_CPU_FREQUENCY / 44100.;
			return {data.first, data.second};
		}
		return {};
	}
}