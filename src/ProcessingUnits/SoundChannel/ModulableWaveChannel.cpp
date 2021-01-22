/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** ModulableWaveChannel.cpp
*/

#include "ModulableWaveChannel.hpp"
#include "../../Timing/Timer.hpp"

namespace GBEmulator::SoundChannel
{
	ModulableWaveChannel::ModulableWaveChannel(GBEmulator::ISound &soundInterface) :
		SoundChannel(soundInterface),
		_wpRAM(CHANSIZE_WPRAM, CHANSIZE_WPRAM)
	{
		this->_sound.setWave(getWavePattern(), 44100);
	}

	std::vector<unsigned char> ModulableWaveChannel::getWavePattern() const
	{
		static std::vector<unsigned char>	raw(4096LLU);

		for (int i = 0; i < 4096 / 2; i += 1) {
			unsigned char wpRam = this->_wpRAM.read(i % 16);

			raw[i * 2]     = (wpRam >> 4U)  << 4U | 0xFU;
			raw[i * 2 + 1] = (wpRam & 0xFU) << 4U | 0xFU;
		}
		return (raw);
	}

	void ModulableWaveChannel::_update(unsigned)
	{
		if (this->_genWave) {
			this->_genWave = false;
			this->_sound.setWave(getWavePattern(), 44100);
		}
	}

	void ModulableWaveChannel::_checkRestart()
	{
		if (
			this->_restartType &&
			this->_volumeCycles > Timing::getCyclesPerSecondsFromFrequency(2.f / (256 - this->_soundLength))
		) {
			this->_soundOn = false;
			this->_restart = false;
			this->_sound.setVolume(0);
		}
	}

	unsigned char ModulableWaveChannel::getSoundOnOff() const
	{
		return (this->_soundOn << 7U) | 0b01111111U;
	}

	unsigned char ModulableWaveChannel::getOutputLevel() const
	{
		return 0b10011111U | (this->_waveOutputLevel << 5U);
	}

	unsigned char ModulableWaveChannel::read(unsigned char address) const
	{
		return this->_wpRAM.read(address);
	}

	void ModulableWaveChannel::setSoundOnOff(unsigned char value)
	{
		this->_soundOn = value >> 7U;
		this->_restart &= this->_soundOn;
		this->_sound.setVolume(this->_soundOn * this->_initialVolume * 100.f / 31);
	}

	void ModulableWaveChannel::setSoundLength(unsigned char value)
	{
		this->_soundLength = value;
	}

	void ModulableWaveChannel::setOutputLevel(unsigned char value)
	{
		this->_waveOutputLevel = (value & 0b01100000U) >> 5U;
		switch (this->_waveOutputLevel) {
		case 0:
			this->_initialVolume = 0;
			break;
		default:
			this->_initialVolume = 0x1FU >> (this->_waveOutputLevel - 1);
			break;
		}
		this->setVolume(this->_initialVolume * 100.f / 31);
	}

	void ModulableWaveChannel::write(unsigned char address, unsigned char value)
	{
		this->_wpRAM.write(address, value);
		this->_genWave = true;
	}

	void ModulableWaveChannel::setLowFrequency(unsigned char value)
	{
		this->_frequency = (this->_frequency & 0b11100000000U) | value;
		this->_realFrequency = 65536.f / (2048 - this->_frequency);
		this->_sound.setPitch(this->_realFrequency / 2760);
	}

	void ModulableWaveChannel::setRestartOptions(unsigned char value)
	{
		unsigned short val = (value & 0b00000111U) << 8U;

		this->_restart = value >> 7U;
		this->_restartType = (value & 0b01000000U) >> 6U;
		this->_frequency = (this->_frequency & 0b00011111111U) | val;
		this->_realFrequency = 65536.f / (2048 - this->_frequency);
		this->_sound.setPitch(this->_realFrequency / 2760);
	}
}