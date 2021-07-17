//
// Created by andgel on 05/05/2021
//

#include "SquareWaveChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator
{
	void SquareWaveChannel::_clockLength()
	{
		if (!this->_frequencyRegister.useLength)
			return;

		if (this->_skipLength) {
			this->_skipLength = false;
			return;
		}
		this->_soundLenPatternDutyRegister.length++;
		this->_expired |= !this->_soundLenPatternDutyRegister.length;
	}

	void SquareWaveChannel::_clockVolume()
	{
		if (!this->_effectiveVolumeEnvelopeRegister.numberOfSweeps)
			return;

		this->_volumeClockCount++;
		if (this->_volumeClockCount >= this->_effectiveVolumeEnvelopeRegister.numberOfSweeps) {
			this->_volumeClockCount = (this->_volumeClockCount > this->_effectiveVolumeEnvelopeRegister.numberOfSweeps);
			if (this->_effectiveVolumeEnvelopeRegister.increases) {
				if (this->_effectiveVolumeEnvelopeRegister.initialVolume != 15)
					this->_effectiveVolumeEnvelopeRegister.initialVolume++;
			} else {
				if (this->_effectiveVolumeEnvelopeRegister.initialVolume != 0)
					this->_effectiveVolumeEnvelopeRegister.initialVolume--;
			}
		}
	}

	void SquareWaveChannel::_clockSweep()
	{
		if (!this->_sweepRegister.sweepTime) {
			this->_sweepClockCount = 0;
			return;
		}

		this->_sweepClockCount++;
		if (this->_sweepClockCount >= this->_sweepRegister.sweepTime) {
			this->_sweepClockCount = (this->_sweepClockCount > this->_sweepRegister.sweepTime);
			if (this->_sweepRegister.substract)
				this->_sweepFrequencyShadow -= this->_sweepFrequencyShadow >> this->_sweepRegister.sweepShifts;
			else
				this->_sweepFrequencyShadow += this->_sweepFrequencyShadow >> this->_sweepRegister.sweepShifts;
			if (this->_sweepFrequencyShadow > 0x7FF)
				this->_expired = true;
			else
				this->_frequencyRegister.setFrequency(this->_sweepFrequencyShadow);
		}
	}

	void SquareWaveChannel::_clockUpdate()
	{
		switch (this->_clockStep) {
		case 2:
		case 6:
			this->_clockSweep();
		case 0:
		case 4:
			this->_clockLength();
			break;
		case 7:
			this->_clockVolume();
			break;
		default:
			break;
		}
		this->_clockStep++;
		this->_clockStep &= 0b111;
	}

	void SquareWaveChannel::_update(unsigned int cycles)
	{
		double frequencyCount = Timing::getCyclesPerSecondsFromFrequency(this->_frequencyRegister.getActualFrequency());
		double clockCount = Timing::getCyclesPerSecondsFromFrequency(512);

		this->_clockCounter += cycles;
		this->_frequencyCounter += cycles;
		while (this->_frequencyCounter >= frequencyCount)
			this->_frequencyCounter -= frequencyCount;

		while (this->_clockCounter >= clockCount) {
			this->_clockCounter -= clockCount;
			this->_clockUpdate();
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
			break;
		case SQUARE_CHANNEL_VOLUME_ENVELOPE:
			this->_volumeEnvelopeRegister = value;
			this->_effectiveVolumeEnvelopeRegister = value;
			this->_volumeClockCount = 0;
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
			if (this->_frequencyRegister.useLength || (this->_frequencyRegister.initial && this->_volumeEnvelopeRegister.initialVolume)) {
				this->_restart();
				if (
					(this->_clockStep & 1) == 1 &&
					this->_frequencyRegister.useLength && (
						this->_frequencyRegister.initial ||
						!old && this->_soundLenPatternDutyRegister.length
					)
				) {
					this->_soundLenPatternDutyRegister.length++;
					this->_expired |= !this->_soundLenPatternDutyRegister.length;
				}
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
		this->_frequencyCounter = 0;
		this->_volumeClockCount = 0;
		this->_sweepClockCount = 0;
		this->_expired = false;
		this->_sweepFrequencyShadow = this->_frequencyRegister.getFrequency();
		this->_effectiveVolumeEnvelopeRegister = this->_volumeEnvelopeRegister;
	}

	void SquareWaveChannel::onPowerOff()
	{
		this->_volumeClockCount = 0;
		this->_sweepClockCount = 0;
		this->_clockCounter = 0;
		this->_clockStep = 0;
		this->_effectiveVolumeEnvelopeRegister = 0;
		this->_sweepRegister = 0;
		this->_soundLenPatternDutyRegister = 0;
		this->_frequencyRegister.loFrequency = 0;
		this->_frequencyRegister.setHigh(0);
		this->_expired = true;
	}
}