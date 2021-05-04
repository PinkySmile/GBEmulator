/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SoundPlayer.cpp
*/

#include <iostream>
#include <cassert>
#include "SFMLSoundPlayer.hpp"

namespace GBEmulator
{
	SFMLSoundPlayer::SFMLSoundPlayer()
	{
		this->initialize(2, 44100);
		this->_samples.resize(100);
		this->play();
	}

	void SFMLSoundPlayer::setVolume(float volume)
	{
		SoundSource::setVolume(volume);
	}

	bool SFMLSoundPlayer::onGetData(sf::SoundStream::Chunk &data)
	{
		while (this->mutex);
		this->mutex = true;
		this->_buffer.swap(this->_samples);
		this->mutex = false;
		data.sampleCount = this->_buffer.size();
		data.samples = this->_buffer.data();
		return true;
	}

	void SFMLSoundPlayer::onSeek(sf::Time)
	{
		assert(false);
	}

	void SFMLSoundPlayer::pushSamples(short *samples, size_t sampleCount)
	{
		while (this->mutex);
		this->mutex = true;
		this->_samples = {samples, samples + sampleCount};
		this->mutex = false;
	}
}
