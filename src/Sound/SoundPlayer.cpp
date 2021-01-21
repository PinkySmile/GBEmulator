/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SoundPlayer.cpp
*/

#include <iostream>
#include "SoundPlayer.hpp"

namespace GBEmulator
{
	SoundPlayer::SoundPlayer() :
		_volume(0)
	{
		this->_soundSO1.setBuffer(this->_soundBuffer);
		this->_soundSO1.setVolume(0);
		this->_soundSO1.play();
		this->_soundSO1.setLoop(true);
		this->_soundSO1.setPosition(1, 0, 0);

		this->_soundSO2.setBuffer(this->_soundBuffer);
		this->_soundSO2.setVolume(0);
		this->_soundSO2.play();
		this->_soundSO2.setLoop(true);
		this->_soundSO2.setPosition(-1, 0, 0);
	}

	void SoundPlayer::setPitch(float pitch)
	{
		this->_soundSO1.setPitch(pitch);
		this->_soundSO2.setPitch(pitch);
	}

	void SoundPlayer::setDisabled(bool disabled) {
		if (disabled) {
			this->_soundSO1.stop();
			this->_soundSO2.stop();
		} else {
			this->_soundSO1.play();
			this->_soundSO2.play();
		}
		this->_disabled = disabled;
	}

	void SoundPlayer::setWave(std::vector<unsigned char> wave, unsigned int sampleRate)
	{
		auto buff = new sf::Int16[wave.size()];

		for (size_t i = 0; i < wave.size(); i++) {
			buff[i] = static_cast<char>(wave[i]) << 8U | (wave[i] != 0 ? 0xFF : 0);
			buff[i] ^= 0x8000U;
		}
		if (!this->_soundBuffer.loadFromSamples(buff, wave.size(), 1, sampleRate))
			throw std::invalid_argument("Cannot load sound buffer");
		delete[] buff;
		this->_soundSO1.setBuffer(this->_soundBuffer);
		this->_soundSO2.setBuffer(this->_soundBuffer);
		this->_soundSO1.setVolume(this->_volume * this->_volumeSO1 / 100);
		this->_soundSO2.setVolume(this->_volume * this->_volumeSO2 / 100);
		this->_soundSO1.setLoop(true);
		this->_soundSO2.setLoop(true);
		this->_soundSO1.setPosition(1, 0, 0);
		this->_soundSO2.setPosition(-1, 0, 0);
		if (!this->_disabled) {
			this->_soundSO1.play();
			this->_soundSO2.play();
		}
	}

	void SoundPlayer::setVolume(float volume)
	{
		this->_volume = volume;
		this->_soundSO1.setVolume(volume * this->_volumeSO1 / 100);
		this->_soundSO2.setVolume(volume * this->_volumeSO2 / 100);
	}

	void SoundPlayer::setSO1Volume(float volume)
	{
		this->_volumeSO1 = volume;
		this->_soundSO1.setVolume(volume * this->_volume / 100);
	}

	void SoundPlayer::setSO2Volume(float volume)
	{
		this->_volumeSO2 = volume;
		this->_soundSO2.setVolume(volume * this->_volume / 100);
	}
}
