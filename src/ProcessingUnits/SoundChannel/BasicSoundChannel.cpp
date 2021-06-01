//
// Created by andgel on 04/05/2021
//

#ifdef ARDUINO
#include <stdint.h>
#include "../../ArduinoStuff/Algorithm.h"
#else
#include <cstdint>
#endif
#include "BasicSoundChannel.hpp"
#include "../../Timing/Timer.hpp"

#define min(x, y) ((x) > (y) ? (y) : (x))

namespace GBEmulator
{
	standard::vector<uint16_t> BasicSoundChannel::update(unsigned int cycles)
	{
		if (!this->hasExpired())
			this->_update(cycles);
		this->_cycles += cycles;
		if (this->_cycles >= GB_CPU_FREQUENCY / SAMPLE_RATE) {
			uint16_t data = min(this->hasExpired() ? 0 : this->_getSoundData(), SOUND_VALUE * 2 - 1);

			this->_cycles -= GB_CPU_FREQUENCY / SAMPLE_RATE;
			return {data, data};
		}
		return {};
	}
}