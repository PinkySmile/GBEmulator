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
		double lengthCount = Timing::getCyclesPerSecondsFromFrequency(256);

		this->_lfsrCounter += cycles;
		this->_volumeEnvelopeCounter += cycles;

		while (
			this->_effectiveVolumeEnvelopeRegister.numberOfSweeps &&
			this->_volumeEnvelopeCounter >= volumeCount
		) {
			this->_volumeEnvelopeCounter -= volumeCount;
			if (volumeCount == 0) {
				this->_volumeEnvelopeCounter = 0;
				break;
			}
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

		while (this->_lengthCounter >= lengthCount) {
			this->_lengthCounter -= lengthCount;
			if (this->hasExpired())
				continue;
			if (!this->_useLength)
				continue;
			this->_length--;
			this->_expired |= !this->_length;
		}
	}

	short NoiseWaveChannel::_getSoundData() const
	{
		short realValue = 2 * SOUND_VALUE * this->_effectiveVolumeEnvelopeRegister.initialVolume / 15;

		if (this->_lfsr & 1)
			return -SOUND_VALUE;
		return realValue - SOUND_VALUE;
	}

	void NoiseWaveChannel::write(unsigned int relativeAddress, unsigned char value)
	{
		switch (relativeAddress) {
		case NOISE_CHANNEL_SOUND_LENGTH:
			this->_length = value;
			this->_expired |= this->_length == 0 && this->_useLength;
			break;
		case NOISE_CHANNEL_VOLUME:
			this->_volumeEnvelopeRegister = value;
			this->_effectiveVolumeEnvelopeRegister = value;
			this->_volumeEnvelopeCounter = 0;
			if (this->_volumeEnvelopeRegister.initialVolume == 0)
				this->_expired = true;
			break;
		case NOISE_CHANNEL_POLYNOMIAL_COUNTER:
			this->_polynomialCounter = value;
			this->_lfsr = 0x7FFF;
			break;
		case NOISE_CHANNEL_COUNTER_CONSEC_INITIAL:
			this->_initial = value & 0x80;
			this->_useLength = value & 0x40;
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
			return this->_initial << 7 | this->_useLength << 6 | 0x3F;
		default:
			return 0xFF;
		}
	}

	void NoiseWaveChannel::_restart()
	{
		this->_lfsr = 0x7FFF;
		this->_expired = false;
		this->_volumeEnvelopeCounter = 0;
		this->_effectiveVolumeEnvelopeRegister = this->_volumeEnvelopeRegister;
	}
}