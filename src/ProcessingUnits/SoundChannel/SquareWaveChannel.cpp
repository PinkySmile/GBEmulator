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
			if (!this->_frequencyRegister.useLength)
				continue;
			this->_soundLenPatternDutyRegister.length++;
			this->_expired |= !this->_soundLenPatternDutyRegister.length;
		}
	}

	uint16_t SquareWaveChannel::_getSoundData() const
	{
		auto v = Timing::getCyclesPerSecondsFromFrequency(this->_frequencyRegister.getActualFrequency());
		uint16_t realValue = 2 * SOUND_VALUE * this->_effectiveVolumeEnvelopeRegister.initialVolume / 15;

		switch (this->_soundLenPatternDutyRegister.patternDuty) {
		case DUTY_12_5_PERCENT:
			v *= 12.5 / 100;
			break;
		case DUTY_25_PERCENT:
			v *= 25.0 / 100;
			break;
		case DUTY_50_PERCENT:
			v *= 50.0 / 100;
			break;
		case DUTY_75_PERCENT:
			v *= 75.0 / 100;
			break;
		}
		if (this->_frequencyCounter > v)
			return 0;
		return realValue;
	}

	void SquareWaveChannel::write(unsigned int relativeAddress, uint8_t value)
	{
		switch (relativeAddress) {
		case SQUARE_CHANNEL_SWEEP_REGISTER:
			this->_sweepRegister = value;
			break;
		case SQUARE_CHANNEL_SOUND_LENGTH_WAVE_PATTERN_DUTY:
			this->_soundLenPatternDutyRegister = value;
			this->_lengthCounter = 0;
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
		default:
			break;
		case SQUARE_CHANNEL_FREQUENCY_HI:
			auto old = this->_frequencyRegister.useLength;

			this->_frequencyRegister.setHigh(value);
			if (this->_frequencyRegister.useLength || (this->_frequencyRegister.initial && this->_volumeEnvelopeRegister.initialVolume))
				this->_restart();
			//if (this->_frequencyRegister.useLength && !old)
			//	this->_lengthCounter = 0;
			if (
				this->_frequencyRegister.useLength && !old &&
				!this->_frequencyRegister.initial &&
				this->_lengthCounter < Timing::getCyclesPerSecondsFromFrequency(512) &&
				this->_soundLenPatternDutyRegister.length
			) {
				this->_soundLenPatternDutyRegister.length++;
				this->_expired |= !this->_soundLenPatternDutyRegister.length;
			}
			break;
		}
	}

	uint8_t SquareWaveChannel::read(unsigned int relativeAddress)
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
		this->_sweepFrequencyShadow = this->_frequencyRegister.getFrequency();
		this->_effectiveVolumeEnvelopeRegister = this->_volumeEnvelopeRegister;
	}

	void SquareWaveChannel::onPowerOff()
	{
		this->_volumeEnvelopeRegister = 0;
		this->_effectiveVolumeEnvelopeRegister = 0;
		this->_sweepRegister = 0;
		this->_soundLenPatternDutyRegister = 0;
		this->_frequencyRegister.loFrequency = 0;
		this->_frequencyRegister.setHigh(0);
		this->_expired = true;
	}
}