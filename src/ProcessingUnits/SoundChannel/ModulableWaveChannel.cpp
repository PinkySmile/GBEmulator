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
	}

	void ModulableWaveChannel::_update(unsigned)
	{
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

	unsigned char ModulableWaveChannel::getSoundLength() const
	{
		return this->_soundLength;
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
		this->_sound.setVolume(this->_soundOn * this->_initialVolume * 100.f / 15);
	}

	void ModulableWaveChannel::setSoundLength(unsigned char value)
	{
		this->_soundLength = value;
	}

	void ModulableWaveChannel::setOutputLevel(unsigned char value)
	{
		this->_waveOutputLevel = (value & 0b10011111U) >> 5U;
	}

	void ModulableWaveChannel::write(unsigned char address, unsigned char value)
	{
		this->_wpRAM.write(address, value);
	}

}