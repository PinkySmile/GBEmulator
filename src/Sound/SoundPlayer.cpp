/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SoundPlayer.cpp
*/

#include "SoundPlayer.hpp"

namespace GBEmulator
{
	GBEmulator::SoundPlayer::SoundPlayer() :
		_volume(0)
	{
		this->_sound.setBuffer(this->_soundBuffer);
		this->_sound.setVolume(0);
		this->_sound.play();
		this->_sound.setLoop(true);
	}

	void GBEmulator::SoundPlayer::setPitch(float pitch)
	{
		this->_sound.setPitch(pitch);
	}

	void SoundPlayer::setDisabled(bool disabled) {
		if (disabled)
			this->_sound.stop();
		else
			this->_sound.play();
		this->_disabled = disabled;
	}

	void GBEmulator::SoundPlayer::setWave(std::vector<unsigned char> wave, unsigned int sampleRate)
	{
		auto buff = new sf::Int16[wave.size()];

		for (size_t i = 0; i < wave.size(); i++)
			buff[i] = static_cast<char>(wave[i]) * 256;
		if (!this->_soundBuffer.loadFromSamples(buff, wave.size(), 1, sampleRate))
			throw std::invalid_argument("Cannot load sound buffer");
		delete[] buff;
		this->_sound.setBuffer(this->_soundBuffer);
		this->_sound.setVolume(this->_volume);
		if (!this->_disabled)
			this->_sound.play();
		this->_sound.setLoop(true);
	}

	void GBEmulator::SoundPlayer::setVolume(float volume)
	{
		this->_volume = volume;
		this->_sound.setVolume(volume);
	}

}
