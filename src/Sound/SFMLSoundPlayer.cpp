/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SoundPlayer.cpp
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <thread>
#include "SFMLSoundPlayer.hpp"

namespace GBEmulator
{
	SFMLSoundPlayer::SFMLSoundPlayer()
	{
		this->initialize(2, 44100);
	}

	SFMLSoundPlayer::~SFMLSoundPlayer()
	{
		while (this->mutex);
		this->mutex = true;
		for (auto &sample : this->_samples)
			sample.resize(40000);
		this->mutex = false;
		this->stop();
	}

	void SFMLSoundPlayer::setVolume(float volume)
	{
		SoundSource::setVolume(volume);
	}

	bool SFMLSoundPlayer::onGetData(sf::SoundStream::Chunk &data)
	{
		while (this->mutex || this->_samples[this->readHead].empty())
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		this->mutex = true;
		this->_buffer = this->_samples[this->readHead];
		this->_samples[this->readHead].clear();
		this->mutex = false;
		this->readHead = (this->readHead + 1) % NB_SAMPLE_BUFFER;
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
		this->_samples[this->writeHead] = {samples, samples + sampleCount};
		this->mutex = false;
		this->writeHead = (this->writeHead + 1) % NB_SAMPLE_BUFFER;
		if (this->getStatus() != sf::Sound::Status::Playing)
			this->play();
	}
}
