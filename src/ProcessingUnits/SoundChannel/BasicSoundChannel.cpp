//
// Created by andgel on 04/05/2021
//

#include "BasicSoundChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator
{
	std::vector<short> BasicSoundChannel::update(unsigned int cycles)
	{
		if (!this->hasExpired())
			this->_update(cycles);
		this->_cycles += cycles;
		if (this->_cycles >= GB_CPU_FREQUENCY / SAMPLE_RATE) {
			short data = this->hasExpired() ? 0 : this->_getSoundData();

			this->_cycles -= GB_CPU_FREQUENCY / SAMPLE_RATE;
			return {data, data};
		}
		return {};
	}
}