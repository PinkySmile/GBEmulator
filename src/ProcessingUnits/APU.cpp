/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.cpp
*/

#ifndef ARDUINO
#include <cassert>
#else
#include <assert.h>
#endif
#include "APU.hpp"
#include "SoundChannel/BasicSoundChannel.hpp"
#include "SoundChannel/SquareWaveChannel.hpp"
#include "SoundChannel/ModulableWaveChannel.hpp"
#include "SoundChannel/NoiseWaveChannel.hpp"

#define SAMPLE_BUFFER_SIZE 4000

namespace GBEmulator
{
	APU::APU(ISound &soundPlayer) :
		_soundPlayer(soundPlayer),
		_channels{
			standard::make_unique<SquareWaveChannel>(),
			standard::make_unique<SquareWaveChannel>(),
			standard::make_unique<ModulableWaveChannel>(),
			standard::make_unique<NoiseWaveChannel>()
		}
	{
		this->_samples._buffer.resize(SAMPLE_BUFFER_SIZE);
		this->_soundPlayer.pushSamples(this->_samples._buffer.data(), this->_samples._buffer.size());
		this->_samples._buffer.clear();
	}

	void APU::update(unsigned cycle)
	{
		if (!this->_enabled) {
			this->_samples = standard::vector<int16_t>{};
			return;
		}
		this->_samples.leftVolume = this->_channelControl.SO1volume / 7.f;
		this->_samples.rightVolume = this->_channelControl.SO2volume / 7.f;
		this->_samples << this->_updateAndProcessChannelSound(0, cycle);
		this->_samples += this->_updateAndProcessChannelSound(1, cycle);
		this->_samples += this->_updateAndProcessChannelSound(2, cycle);
		this->_samples += this->_updateAndProcessChannelSound(3, cycle);
		if (this->_samples._buffer.size() >= SAMPLE_BUFFER_SIZE) {
			this->_soundPlayer.pushSamples(this->_samples._buffer.data(), this->_samples._buffer.size());
			this->_samples._buffer.clear();
		}
	}

	void APU::write(uint16_t address, uint8_t value)
	{
		if (address >= WPRAM_START && address <= WPRAM_END)
			return this->_channels[2]->write(address - NR30, value);
		if (!this->_enabled && address != NR52)
			return;
		if (address >= NR10 && address <= NR14)
			return this->_channels[0]->write(address - NR10, value);
		if (address >= NR21 && address <= NR24)
			return this->_channels[1]->write(address - NR20, value);
		if (address >= NR30 && address <= NR34)
			return this->_channels[2]->write(address - NR30, value);
		if (address >= NR41 && address <= NR44)
			return this->_channels[3]->write(address - NR40, value);
		if (address >= NR50 && address <= NR52)
			return this->_internalWrite(address - NR50, value);
	}

	unsigned char APU::read(uint16_t address) const
	{
		if (address >= WPRAM_START && address <= WPRAM_END)
			return this->_channels[2]->read(address - NR30);
		if (!this->_enabled && address != NR52)
			return 0xFF;
		if (address >= NR10 && address <= NR14)
			return this->_channels[0]->read(address - NR10);
		//NR20 Doesn't actually exist
		if (address >= NR21 && address <= NR24)
			return this->_channels[1]->read(address - NR20);
		if (address >= NR30 && address <= NR34)
			return this->_channels[2]->read(address - NR30);
		//NR40 Doesn't actually exist
		if (address >= NR41 && address <= NR44)
			return this->_channels[3]->read(address - NR40);
		if (address >= NR50 && address <= NR52)
			return this->_internalRead(address - NR50);
		return 0xFF;
	}

	void APU::_internalWrite(unsigned short relativeAddress, uint8_t value)
	{
		switch (relativeAddress) {
		case APU_CHANNEL_CONTROL:
			this->_channelControl = value;
			break;
		case APU_SOT_SELECTION:
			this->_terminalSelect = value;
			break;
		case APU_SOUND_ON_OFF:
			if (this->_enabled && (value & 0x80) == 0)
				for (auto &channel : this->_channels)
					channel->onPowerOff();
			this->_enabled = (value & 0x80) != 0;
			break;
		default:
			break;
		}
	}

	unsigned char APU::_internalRead(unsigned short relativeAddress) const
	{
		switch (relativeAddress) {
		case APU_CHANNEL_CONTROL:
			return this->_channelControl;
		case APU_SOT_SELECTION:
			return this->_terminalSelect;
		default:
			return 0xFF;
		case APU_SOUND_ON_OFF:
			unsigned char v = 0;

			for (int i = 4; i; i--) {
				v <<= 1U;
				v |= !this->_channels[i - 1]->hasExpired();
			}
			return (this->_enabled << 7U) | 0x70 | v;
		}
	}

	standard::vector<int16_t> APU::_updateAndProcessChannelSound(int channelNb, unsigned cycles)
	{
		auto result = this->_channels[channelNb]->update(cycles);
		APUSoundOutputTerminalSelect term = static_cast<unsigned char>(this->_terminalSelect) >> channelNb;

		assert(result.size() % 2 == 0);
		for (unsigned i = 0; i < result.size(); i += 2) {
			if (!term.outputSound1toSO1)
				result[i] = 0;
			if (!term.outputSound1toSO2)
				result[i + 1] = 0;
		}
		return result;
	}

	SampleBuffer &SampleBuffer::operator=(const standard::vector<int16_t> &samples)
	{
		this->_buffer = samples;
		return *this;
	}

	SampleBuffer &SampleBuffer::operator+=(const standard::vector<int16_t> &samples)
	{
		unsigned offset = this->_buffer.size() - samples.size();

		assert(this->_buffer.size() >= samples.size());
		assert(samples.size() % 2 == 0);
		for (unsigned i = 0; i < samples.size(); i += 2) {
			this->_buffer[  i + offset  ] += samples[  i  ] * this->leftVolume;
			this->_buffer[i + offset + 1] += samples[i + 1] * this->rightVolume;
		}
		return *this;
	}

	SampleBuffer &SampleBuffer::operator<<(const standard::vector<int16_t> &samples)
	{
		assert(samples.size() % 2 == 0);
		this->_buffer.reserve(samples.size() + this->_buffer.size());
		for (unsigned i = 0; i < samples.size(); i += 2) {
			this->_buffer.push_back(samples[  i  ] * this->leftVolume);
			this->_buffer.push_back(samples[i + 1] * this->rightVolume);
		}
		return *this;
	}
}