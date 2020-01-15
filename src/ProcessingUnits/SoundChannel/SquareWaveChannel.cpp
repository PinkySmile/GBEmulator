/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SquareWaveChannel.cpp
*/

#include <cmath>
#include "SquareWaveChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator::SoundChannel
{
	std::vector<unsigned char> &SquareWaveChannel::getSquareWave(int frequency, float percentage)
	{
		static std::vector<unsigned char> raw(44100LLU);

		for (int i = 0; i < 44100; i++)
			raw[i] = (std::fmod(i * frequency * 100 / 44100, 100) > percentage ? 127 : -127);
		return (raw);
	}

	SquareWaveChannel::SquareWaveChannel(GBEmulator::ISound &soundInterface) :
		SoundChannel(soundInterface)
	{
	}

	void SquareWaveChannel::update(unsigned cycles)
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

		this->_volumeCycles += cycles;
		this->_sweepCycles += cycles;

		if (this->_volumeShiftNumber) {
			double volume = (
				this->_volumeCycles / (this->_volumeShiftNumber * Timing::getCyclesPerSecondsFromFrequency(64)) *
				(this->_volumeDirection * 2 - 1) + this->_initialVolume
			);

			this->_sound.setVolume((volume > 0 ? (volume > 15 ? 15 : volume) : 0) * 100 / 15);
		}

		if (this->_sweepTime) {
			double realFrequency = 131072.f / (2048 - this->_frequency);

			realFrequency += (
				(this->_sweepCycles / Timing::getCyclesPerSecondsFromFrequency(this->_sweepShiftNumber / 128.)) *
				realFrequency / pow(2, this->_sweepShiftNumber) * (this->_sweepDirection * 2 + 1)
			);
			this->_sound.setPitch(realFrequency / BASE_FREQU);
		}
	}

	void SquareWaveChannel::restart()
	{
	}

	void SquareWaveChannel::_setWave(unsigned char value)
	{
		this->_soundLength = value & 0b00111111U;
		if (this->_wavePattern != value >> 6U) {
			this->_wavePattern = value >> 6U;
			switch (this->_wavePattern) {
			case 0:
				return this->_sound.setWave(getSquareWave(BASE_FREQU, 12.5), 44100);
			case 1:
				return this->_sound.setWave(getSquareWave(BASE_FREQU, 25), 44100);
			case 2:
				return this->_sound.setWave(getSquareWave(BASE_FREQU, 50), 44100);
			case 3:
				return this->_sound.setWave(getSquareWave(BASE_FREQU, 75), 44100);
			default:
				return;
			}
		}
	}

	unsigned char SquareWaveChannel::_getWave()
	{
		return (this->_wavePattern << 6U) | 0b00111111U;
	}

	void SquareWaveChannel::write(unsigned char address, unsigned char value)
	{
		switch (address) {
		case 0:
			return this->_setWave(value);
		default:
			return;
		}
	}

	unsigned char SquareWaveChannel::read(unsigned char address)
	{
		switch (address) {
		case 0:
			return this->_getWave();
		default:
			return 0xFF;
		}
	}
}