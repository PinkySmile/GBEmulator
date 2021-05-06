//
// Created by andgel on 06/05/2021
//

#include <cstdio>
#include "NoiseWaveChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator
{

	void NoiseWaveChannel::_update(unsigned int cycles)
	{
		double volumeCount = this->_effectiveVolumeEnvelopeRegister.numberOfSweeps * Timing::getCyclesPerSecondsFromFrequency(64);
		double lfsrCount = Timing::getCyclesPerSecondsFromFrequency(this->_polynomialCounter.getFrequency());

		this->_lfsrCounter += cycles;
		this->_volumeEnvelopeCounter += cycles;

		while (
			this->_effectiveVolumeEnvelopeRegister.numberOfSweeps &&
			this->_volumeEnvelopeCounter >= volumeCount
		) {
			this->_volumeEnvelopeCounter -= volumeCount;
			if (this->_effectiveVolumeEnvelopeRegister.increases) {
				if (this->_effectiveVolumeEnvelopeRegister.initialVolume != 15)
					this->_effectiveVolumeEnvelopeRegister.initialVolume++;
			} else {
				if (this->_effectiveVolumeEnvelopeRegister.initialVolume != 0)
					this->_effectiveVolumeEnvelopeRegister.initialVolume--;
			}
		}

		while (this->_lfsrCounter >= lfsrCount) {
			auto bit = (this->_lfsr & 1) ^ (this->_lfsr >> 1 & 1);

			this->_lfsrCounter -= lfsrCount;
			this->_lfsr >>= 1;
			this->_lfsr |= bit << 14;
			if (this->_polynomialCounter.isCounter7bits)
				this->_lfsr |= (bit << 6);
		}
	}

	short NoiseWaveChannel::_getSoundData() const
	{
		short realValue = 8160 * this->_effectiveVolumeEnvelopeRegister.initialVolume / 15;

		if (this->_lfsr & 1)
			return -realValue;
		return realValue;
	}

	bool NoiseWaveChannel::hasExpired() const
	{
		return this->_first || (this->_useLength && this->_length == 0);
	}

	void NoiseWaveChannel::write(unsigned int relativeAddress, unsigned char value)
	{
		switch (relativeAddress) {
		case NOISE_CHANNEL_SOUND_LENGTH:
			this->_length = value;
			break;
		case NOISE_CHANNEL_VOLUME:
			this->_volumeEnvelopeRegister = value;
			this->_effectiveVolumeEnvelopeRegister = value;
			this->_volumeEnvelopeCounter = 0;
			break;
		case NOISE_CHANNEL_POLYNOMIAL_COUNTER:
			this->_polynomialCounter = value;
			this->_lfsr = 0x7F;
			break;
		case NOISE_CHANNEL_COUNTER_CONSEC_INITIAL:
			this->_initial = value & 0x80;
			this->_useLength = value & 0x40;
			this->_first = false;
			if (this->_initial)
				this->_restart();
			break;
		default:
			break;
		}
	}

	unsigned char NoiseWaveChannel::read(unsigned int relativeAddress)
	{
		switch (relativeAddress) {
		case NOISE_CHANNEL_SOUND_LENGTH:
			return this->_length | 0xC0;
		case NOISE_CHANNEL_VOLUME:
			return this->_volumeEnvelopeRegister;
		case NOISE_CHANNEL_POLYNOMIAL_COUNTER:
			return this->_polynomialCounter;
		case NOISE_CHANNEL_COUNTER_CONSEC_INITIAL:
			return (this->_initial != 0) << 7 | (this->_useLength != 0) << 6 | 0x3F;
		default:
			return 0xFF;
		}
	}

	void NoiseWaveChannel::_restart()
	{
		this->_volumeEnvelopeCounter = 0;
		this->_effectiveVolumeEnvelopeRegister = this->_volumeEnvelopeRegister;
	}
}