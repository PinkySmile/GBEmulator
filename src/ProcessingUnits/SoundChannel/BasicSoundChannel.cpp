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

namespace GBEmulator
{
	standard::vector<int16_t> BasicSoundChannel::update(unsigned int cycles)
	{
		if (!this->hasExpired())
			this->_update(cycles);
		this->_cycles += cycles;
		if (this->_cycles >= GB_CPU_FREQUENCY / SAMPLE_RATE) {
			int16_t data = standard::clamp<int16_t>(this->hasExpired() ? -SOUND_VALUE : this->_getSoundData(), -SOUND_VALUE, SOUND_VALUE - 1);

			this->_cycles -= GB_CPU_FREQUENCY / SAMPLE_RATE;
			return {data, data};
		}
		return {};
	}
}