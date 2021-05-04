/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.cpp
*/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <cassert>
#include "APU.hpp"
#include "SoundChannel/BasicSoundChannel.hpp"
#include "../Timing/Timer.hpp"

namespace GBEmulator
{
	APU::APU(ISound &soundPlayer) :
		_soundPlayer(soundPlayer),
		_channels{
			std::make_unique<BasicSoundChannel>(),
			std::make_unique<BasicSoundChannel>(),
			std::make_unique<BasicSoundChannel>(),
			std::make_unique<BasicSoundChannel>()
		}
	{
	}

	void APU::update(unsigned cycle)
	{
		this->_samples << this->_channels[0]->update(cycle);
		this->_samples += this->_channels[1]->update(cycle);
		this->_samples += this->_channels[2]->update(cycle);
		this->_samples += this->_channels[3]->update(cycle);
		if (this->_samples._buffer.size() >= 1000) {
			this->_soundPlayer.pushSamples(this->_samples._buffer.data(), this->_samples._buffer.size());
			this->_samples = std::vector<short>{};
		}
	}

	void APU::write(unsigned short address, unsigned char value)
	{
		if (address >= NR10 && address <= NR14)
			return this->_channels[0]->write(address - NR10, value);
		if (address >= NR21 && address <= NR24)
			return this->_channels[1]->write(address - NR21, value);
		if (address >= NR30 && address <= NR34)
			return this->_channels[2]->write(address - NR30, value);
		if (address >= NR41 && address <= NR44)
			return this->_channels[3]->write(address - NR41, value);
		if (address >= WPRAM_START && address <= WPRAM_END)
			return this->_channels[2]->write(address - NR30, value);
	}

	unsigned char APU::read(unsigned short address) const
	{
		if (address >= NR10 && address <= NR14)
			return this->_channels[0]->read(address - NR10);
		if (address >= NR21 && address <= NR24)
			return this->_channels[1]->read(address - NR21);
		if (address >= NR30 && address <= NR34)
			return this->_channels[2]->read(address - NR30);
		if (address >= NR41 && address <= NR44)
			return this->_channels[3]->read(address - NR41);
		if (address >= WPRAM_START && address <= WPRAM_END)
			return this->_channels[2]->read(address - NR30);
		return 0xFF;
	}

	SampleBuffer &SampleBuffer::operator=(const std::vector<short> &samples)
	{
		this->_buffer = samples;
		return *this;
	}

	SampleBuffer &SampleBuffer::operator+=(const std::vector<short> &samples)
	{
		unsigned offset = this->_buffer.size() - samples.size();

		assert(this->_buffer.size() >= samples.size());
		for (unsigned i = 0; i < samples.size(); i++)
			this->_buffer[i + offset] += samples[i];
		return *this;
	}

	SampleBuffer &SampleBuffer::operator<<(const std::vector<short> &samples)
	{
		this->_buffer.reserve(samples.size() + this->_buffer.size());
		for (auto sample : samples)
			this->_buffer.push_back(sample);
		return *this;
	}
}