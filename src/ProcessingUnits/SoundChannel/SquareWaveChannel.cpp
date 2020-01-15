/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SquareWaveChannel.cpp
*/

#include <cmath>
#include "SquareWaveChannel.hpp"

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
		SoundChannel(soundInterface),
		_waves{
			getSquareWave(BASE_FREQU, 12.5),
			getSquareWave(BASE_FREQU, 25),
			getSquareWave(BASE_FREQU, 50),
			getSquareWave(BASE_FREQU, 75),
		}
	{
	}

	void SquareWaveChannel::_update(unsigned)
	{
	}

	void SquareWaveChannel::restart()
	{
	}

	void SquareWaveChannel::_setWave(unsigned char value)
	{
		this->_soundLength = value & 0b00111111U;
		if (this->_wavePattern != value >> 6U) {
			this->_wavePattern = value >> 6U;
			this->_sound.setWave(this->_waves[this->_wavePattern], 44100);
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