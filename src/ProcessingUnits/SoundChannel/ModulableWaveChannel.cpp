//
// Created by andgel on 05/05/2021
//

#ifdef ARDUINO
#include <stdlib.h>
#else
#include <cstdlib>
#endif
#include "ModulableWaveChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator
{
	void ModulableWaveChannel::_update(unsigned int cycles)
	{
		auto required = Timing::getCyclesPerSecondsFromFrequency(this->_frequencyRegister.getActualFrequency() * 0x10);
		double lengthCount = Timing::getCyclesPerSecondsFromFrequency(256);

		this->_nextByteCounter += cycles;
		while (this->_nextByteCounter >= required) {
			this->_nextByteCounter -= required;
			this->_current = (this->_current + 1) % 0x20;
		}

		this->_lengthCounter += cycles;
		while (this->_lengthCounter >= lengthCount) {
			this->_lengthCounter -= lengthCount;
			if (!this->_frequencyRegister.useLength)
				continue;
			this->_length++;
			this->_expired |= !this->_length;
		}
	}

	uint16_t ModulableWaveChannel::_getSoundData() const
	{
		if (this->_volume == 0)
			return 0;

		uint16_t realVal = this->_wpram[this->_current];

		realVal >>= (this->_volume - 1);
		realVal <<= 10;
		return realVal;
	}

	void ModulableWaveChannel::write(unsigned int relativeAddress, uint8_t value)
	{
		switch (relativeAddress) {
		case MODULABLE_CHANNEL_ON_OFF:
			this->_enabled = value & 0x80;
			this->_expired |= !this->_enabled;
			break;
		case MODULABLE_CHANNEL_SOUND_LENGTH:
			this->_length = value;
			break;
		case MODULABLE_CHANNEL_VOLUME:
			this->_volume = static_cast<OutputLevel>(value >> 5 & 3);
			break;
		case MODULABLE_CHANNEL_FREQUENCY_LO:
			this->_frequencyRegister.loFrequency = value;
			break;
		case MODULABLE_CHANNEL_FREQUENCY_HI:
			this->_frequencyRegister.setHigh(value);
			if (this->_frequencyRegister.useLength || this->_frequencyRegister.initial && this->_enabled)
				this->_restart();
			break;
		default:
			if (relativeAddress >= MODULABLE_CHANNEL_WPRAM_START && relativeAddress <= MODULABLE_CHANNEL_WPRAM_END) {
				this->_wpram[(relativeAddress - MODULABLE_CHANNEL_WPRAM_START) * 2] = value >> 4;
				this->_wpram[(relativeAddress - MODULABLE_CHANNEL_WPRAM_START) * 2 + 1] = value & 0xF;
				break;
			}
			break;
		}
	}

	uint8_t ModulableWaveChannel::read(unsigned int relativeAddress)
	{
		switch (relativeAddress) {
		case MODULABLE_CHANNEL_ON_OFF:
			return (this->_enabled << 7) | 0x7F;
		case MODULABLE_CHANNEL_VOLUME:
			return this->_volume << 5 | 0x9F;
		case MODULABLE_CHANNEL_SOUND_LENGTH:
		case MODULABLE_CHANNEL_FREQUENCY_LO:
			return 0xFF;
		case MODULABLE_CHANNEL_FREQUENCY_HI:
			return this->_frequencyRegister.getHigh();
		default:
			if (relativeAddress >= MODULABLE_CHANNEL_WPRAM_START && relativeAddress <= MODULABLE_CHANNEL_WPRAM_END) {
				//if (!this->hasExpired())
				//	return (this->_wpram[(this->_current / 2) * 2] << 4 | this->_wpram[(this->_current / 2) * 2 + 1]);
				return this->_wpram[(relativeAddress - MODULABLE_CHANNEL_WPRAM_START) * 2] << 4 | this->_wpram[(relativeAddress - MODULABLE_CHANNEL_WPRAM_START) * 2 + 1];
			}
			return 0xFF;
		}
	}

	void ModulableWaveChannel::_restart()
	{
		this->_expired = false;
		this->_current = 0;
		this->_nextByteCounter = 0;
	}

	void ModulableWaveChannel::onPowerOff()
	{
		this->_enabled = false;
		this->_length = 0;
		this->_volume = OUTPUT_MUTED;
		this->_frequencyRegister.loFrequency = 0;
		this->_frequencyRegister.setHigh(0);
		this->_expired = true;
	}

	ModulableWaveChannel::ModulableWaveChannel()
	{
		for (auto &e : this->_wpram)
			e = rand() & 0xF;
	}
}
