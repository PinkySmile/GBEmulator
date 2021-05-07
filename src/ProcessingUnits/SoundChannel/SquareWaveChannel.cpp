//
// Created by andgel on 05/05/2021
//

#include "SquareWaveChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator
{
	void SquareWaveChannel::_update(unsigned int cycles)
	{
		double frequencySweepCount = this->_sweepRegister.sweepTime == 0 ? 0 : Timing::getCyclesPerSecondsFromFrequency(128. / this->_sweepRegister.sweepTime);
		double frequencyCount = Timing::getCyclesPerSecondsFromFrequency(this->_frequencyRegister.getActualFrequency());
		double volumeCount = this->_effectiveVolumeEnvelopeRegister.numberOfSweeps * Timing::getCyclesPerSecondsFromFrequency(64);
		double lengthCount = Timing::getCyclesPerSecondsFromFrequency(256);

		this->_lengthCounter += cycles;
		this->_frequencyCounter += cycles;
		this->_volumeEnvelopeCounter += cycles;
		this->_frequencySweepCounter += cycles;

		while (this->_frequencyCounter >= frequencyCount)
			this->_frequencyCounter -= frequencyCount;

		while (this->_volumeEnvelopeCounter >= volumeCount) {
			this->_volumeEnvelopeCounter -= volumeCount;
			if (volumeCount == 0) {
				this->_volumeEnvelopeCounter = 0;
				break;
			}
			if (!this->_effectiveVolumeEnvelopeRegister.numberOfSweeps)
				continue;
			if (this->_effectiveVolumeEnvelopeRegister.increases) {
				if (this->_effectiveVolumeEnvelopeRegister.initialVolume != 15)
					this->_effectiveVolumeEnvelopeRegister.initialVolume++;
			} else {
				if (this->_effectiveVolumeEnvelopeRegister.initialVolume != 0)
					this->_effectiveVolumeEnvelopeRegister.initialVolume--;
			}
		}

		while (this->_frequencySweepCounter >= frequencySweepCount) {
			this->_frequencySweepCounter -= frequencySweepCount;
			if (frequencySweepCount == 0) {
				this->_frequencySweepCounter = 0;
				break;
			}
			if (!this->_sweepRegister.sweepTime)
				continue;
			if (this->_sweepRegister.substract)
				this->_sweepFrequencyShadow -= this->_sweepFrequencyShadow >> this->_sweepRegister.sweepShifts;
			else
				this->_sweepFrequencyShadow += this->_sweepFrequencyShadow >> this->_sweepRegister.sweepShifts;
			if (this->_sweepFrequencyShadow > 0x7FF)
				this->_expired = true;
			else
				this->_frequencyRegister.setFrequency(this->_sweepFrequencyShadow);
		}

		while (this->_lengthCounter > lengthCount) {
			this->_lengthCounter -= lengthCount;
			if (this->hasExpired())
				continue;
			if (!this->_frequencyRegister.useLength)
				continue;
			this->_soundLenPatternDutyRegister.length--;
			this->_expired |= !this->_soundLenPatternDutyRegister.length;
		}
	}

	short SquareWaveChannel::_getSoundData() const
	{
		auto v = Timing::getCyclesPerSecondsFromFrequency(this->_frequencyRegister.getActualFrequency());
		short realValue = 2 * SOUND_VALUE * this->_effectiveVolumeEnvelopeRegister.initialVolume / 15;

		switch (this->_soundLenPatternDutyRegister.patternDuty) {
		case DUTY_12_5_PERCENT:
			v /= 100 / 12.5;
			break;
		case DUTY_25_PERCENT:
			v /= 4;
			break;
		case DUTY_50_PERCENT:
			v /= 2;
			break;
		case DUTY_75_PERCENT:
			v /= 4 / 3.;
			break;
		}

		if (this->_frequencyCounter > v)
			return -SOUND_VALUE;
		return realValue - SOUND_VALUE;
	}

	void SquareWaveChannel::write(unsigned int relativeAddress, unsigned char value)
	{
		switch (relativeAddress) {
		case SQUARE_CHANNEL_SWEEP_REGISTER:
			this->_sweepRegister = value;
			break;
		case SQUARE_CHANNEL_SOUND_LENGTH_WAVE_PATTERN_DUTY:
			this->_soundLenPatternDutyRegister = value;
			this->_lengthCounter = 0;
			this->_expired |= this->_soundLenPatternDutyRegister.length == 0 && this->_frequencyRegister.useLength;
			break;
		case SQUARE_CHANNEL_VOLUME_ENVELOPE:
			this->_volumeEnvelopeRegister = value;
			this->_effectiveVolumeEnvelopeRegister = value;
			this->_volumeEnvelopeCounter = 0;
			if (this->_volumeEnvelopeRegister.initialVolume == 0)
				this->_expired = true;
			break;
		case SQUARE_CHANNEL_FREQUENCY_LO:
			this->_frequencyRegister.loFrequency = value;
			break;
		case SQUARE_CHANNEL_FREQUENCY_HI:
			this->_frequencyRegister.setHigh(value);
			if (this->_frequencyRegister.initial)
				this->_restart();
			break;
		default:
			break;
		}
	}

	unsigned char SquareWaveChannel::read(unsigned int relativeAddress)
	{
		switch (relativeAddress) {
		case SQUARE_CHANNEL_SWEEP_REGISTER:
			return this->_sweepRegister;
		case SQUARE_CHANNEL_SOUND_LENGTH_WAVE_PATTERN_DUTY:
			return this->_soundLenPatternDutyRegister;
		case SQUARE_CHANNEL_VOLUME_ENVELOPE:
			return this->_volumeEnvelopeRegister;
		case SQUARE_CHANNEL_FREQUENCY_HI:
			return this->_frequencyRegister.getHigh();
		case SQUARE_CHANNEL_FREQUENCY_LO:
		default:
			return 0xFF;
		}
	}

	void SquareWaveChannel::_restart()
	{
		this->_expired = false;
		this->_lengthCounter = 0;
		this->_frequencyCounter = 0;
		this->_volumeEnvelopeCounter = 0;
		this->_frequencySweepCounter = 0;
		this->_sweepFrequencyShadow = this->_frequencyRegister.getFrequency();
		this->_effectiveVolumeEnvelopeRegister = this->_volumeEnvelopeRegister;
	}
}