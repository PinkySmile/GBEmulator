/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SoundChannel.cpp
*/

#include <iostream>
#include <cmath>
#include "SoundChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator::SoundChannel
{
	SoundChannel::SoundChannel(GBEmulator::ISound &soundInterface) :
		_sound(soundInterface)
	{
	}

	void SoundChannel::setSweep(unsigned char value)
	{
		this->_sweepTime = (value & 0b01110000U) >> 4U;
		this->_sweepDirection = (value & 0b00001000U) ? DECREASE : INCREASE;
		this->_sweepShiftNumber = (value & 0b00000111U);
	}

	void SoundChannel::setVolume(unsigned char value)
	{
		this->_initialVolume = value >> 4U;
		this->_volumeDirection = (value & 0b00001000U) ? INCREASE : DECREASE;
		this->_volumeShiftNumber = value & 0b00000111U;
		this->_volumeCycles = 0;
		this->_sound.setVolume(this->_soundOn * this->_initialVolume * 100.f / 15);
	}

	void SoundChannel::setLowFrequency(unsigned char value)
	{
		this->_frequency = (this->_frequency & 0b11100000000U) | value;
		this->_sound.setPitch(131072.f / (2048 - this->_frequency) / BASE_FREQU);
	}

	void SoundChannel::setRestartOptions(unsigned char value)
	{
		unsigned short val = (value & 0b00000111U) << 8U;

		this->_restart = value >> 7U;
		this->_restartType = (value & 0b01000000U) >> 6U;
		this->_frequency = (this->_frequency & 0b00011111111U) | val;
		this->_sound.setPitch(131072.f / (2048 - this->_frequency) / BASE_FREQU);
	}

	void SoundChannel::setSOTerminals(bool SO1, bool SO2)
	{
		this->_sound.setSO1(SO1);
		this->_sound.setSO2(SO2);
	}

	void SoundChannel::disable(bool disabled)
	{
		this->_soundOn = !disabled && this->_restart;
		this->_sound.setVolume(this->_soundOn * this->_initialVolume * 100.f / 15);
	}

	void SoundChannel::_updateVolume(unsigned cycles)
	{
		this->_volumeCycles += cycles;

		if (this->_volumeShiftNumber) {
			double volume = (
				this->_volumeCycles / (this->_volumeShiftNumber * Timing::getCyclesPerSecondsFromFrequency(64)) *
				(this->_volumeDirection * 2 - 1) + this->_initialVolume
			);

			this->_sound.setVolume((volume > 0 ? (volume > 15 ? 15 : volume) : 0) * 100 / 15);
		}
	}

	void SoundChannel::_updateSweep(unsigned cycles)
	{
		this->_sweepCycles += cycles;

		if (this->_sweepTime) {
			double realFrequency = 131072.f / (2048 - this->_frequency);

			realFrequency += (
				(this->_sweepCycles / Timing::getCyclesPerSecondsFromFrequency(this->_sweepShiftNumber / 128.)) *
				realFrequency / std::pow(2, this->_sweepShiftNumber) * (this->_sweepDirection * 2 + 1)
			);
			this->_sound.setPitch(realFrequency / BASE_FREQU);
		}
	}

	void SoundChannel::update(unsigned cycles)
	{
		if (!this->_soundOn && this->_restart) {
			this->_soundOn = true;
			this->_sound.setVolume(this->_initialVolume * 100.f / 15);
		}

		if (
			this->_restartType &&
			this->_volumeCycles > Timing::getCyclesPerSecondsFromFrequency(256. / (64 - this->_soundLength))
		) {
			this->_soundOn = false;
			this->_restart = false;
			this->_sound.setVolume(0);
		}

		if (!this->_soundOn)
			return;

		this->_updateVolume(cycles);
		this->_updateSweep(cycles);
		this->_update(cycles);
	}

	unsigned char SoundChannel::getRestartOptions() const
	{
		return (this->_restartType << 6U) | 0b10111111U;
	}

	unsigned char SoundChannel::getSweep() const
	{
		return 0b10000000U | (this->_sweepTime << 4U) | (!this->_sweepDirection << 3U) | this->_sweepShiftNumber;
	}

	unsigned char SoundChannel::getVolume() const
	{
		return (this->_initialVolume << 4U) | (this->_volumeDirection << 3U) | this->_volumeShiftNumber;
	}
}