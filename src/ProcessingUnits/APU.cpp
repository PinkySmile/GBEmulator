/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.cpp
*/

#include <cmath>
#include <cstdio>
#include <iostream>
#include "APU.hpp"
#include "../Timing/Timer.hpp"
#include "SoundChannel/SquareWaveChannel.hpp"

namespace GBEmulator
{
	APU::APU(ISound &channelOne, ISound &channelTwo, ISound &channelThree, ISound &channelFour) :
		_managerChannel1(channelOne),
		_managerChannel2(channelTwo),
		_managerChannelWave(channelThree),
		_managerChannelNoise(channelFour)
	{
	}

	void APU::update(unsigned cycle)
	{
		this->_managerChannel1.update(cycle);
		this->_managerChannel2.update(cycle);
		this->_managerChannelWave.update(cycle);
		this->_managerChannelNoise.update(cycle);
	}

	void APU::write(unsigned short address, unsigned char value)
	{
		switch (address) {
			case FF10 ... FF14 :
				channelOneWriting(address, value);
				break;
			case FF16 ... FF19 :
				channelTwoWriting(address - FF16, value);
				break;
			case FF1A ... FF1E :
				channelWaveWriting(address - FF1A, value);
				break;
			case FF20 ... FF23 :
				channelNoiseWriting(address - FF20, value);
				break;
			case FF24 ... FF26 :
				controllerWriting(address - FF24, value);
				break;
			case WPRAM_START ... WPRAM_END :
				this->_managerChannelWave.write(address - WPRAM_START, value);
				break;
			default :
				break;
		}
	}

	unsigned char APU::read(unsigned short address) const
	{
		switch (address) {
			case FF10 ... FF14 :
				return channelOneReading(address);
			case FF16 ... FF19 :
				return channelTwoReading(address - FF16);
			case FF1A ... FF1E :
				return channelWaveReading(address - FF1A);
			case FF20 ... FF23 :
				return channelNoiseReading(address - FF20);
			case FF24 ... FF26 :
				return controllerReading(address - FF24);
			case WPRAM_START ... WPRAM_END :
				return this->_managerChannelWave.read(address);
			default :
				return 0xFF;

		}
	}

	//
	//ChannelOneReading and Writing
	//

	unsigned char APU::channelOneReading(unsigned short address) const
	{
		switch (address) {
		case 0x0 :
			return this->_managerChannel1.getSweep();
		case 0x1 :
			return this->_managerChannel1.getWave();
		case 0x2 :
			return this->_managerChannel1.getVolume();
		case 0x3 :
			return 0xFF;
		case 0x4 :
			return this->_managerChannel1.getRestartOptions();
		default :
			return 0xFF;
		}
	}

	void APU::channelOneWriting(unsigned short address, unsigned char value)
	{
		switch (address) {
		case 0x0 :
			return this->_managerChannel1.setSweep(value);
		case 0x1 :
			return this->_managerChannel1.setWave(value);
		case 0x2 :
			return this->_managerChannel1.setVolume(value);
		case 0x3 :
			return this->_managerChannel1.setLowFrequency(value);
		case 0x4 :
			return this->_managerChannel1.setRestartOptions(value);
		default :
			return;
		}
	}

	//
	//ChannelTwo Reading and Writing
	//

	unsigned char APU::channelTwoReading(unsigned short address) const
	{
		switch (address) {
		case 0x0 :
			return this->_managerChannel2.getWave();
		case 0x1 :
			return this->_managerChannel2.getVolume();
		case 0x2 :
			return 0xFF;
		case 0x3 :
			return this->_managerChannel2.getRestartOptions();
		default :
			return 0xFF;
		}
	}

	void APU::channelTwoWriting(unsigned short address, unsigned char value)
	{
		switch (address) {
		case 0x0 :
			return this->_managerChannel2.setWave(value);
		case 0x1 :
			return this->_managerChannel2.setVolume(value);
		case 0x2 :
			return this->_managerChannel2.setLowFrequency(value);
		case 0x3 :
			return this->_managerChannel2.setRestartOptions(value);
		default :
			return;
		}
	}

	//
	//ChannelWave Reading and Writing
	//

	unsigned char APU::channelWaveReading(unsigned short address) const
	{
		switch (address) {
			case 0x0 :
				return this->_managerChannelWave.getSoundOnOff();
			case 0x1 :
				return this->_managerChannelWave.getSoundLength();
			case 0x2 :
				return this->_managerChannelWave.getOutputLevel();
			case 0x3 :
				return 0xFF;
			case 0x4 :
				return this->_managerChannelWave.getRestartOptions();
			default :
				return 0xFF;
		}
	}

	void APU::channelWaveWriting(unsigned short address, unsigned char value)
	{
		switch (address) {
			case 0x0 :
				this->_managerChannelWave.setSoundOnOff(value);
				break;
			case 0x1 :
				this->_managerChannelWave.setSoundLength(value);
				break;
			case 0x2 :
				this->_managerChannelWave.setOutputLevel(value);
				break;
			case 0x3 :
				this->_managerChannelWave.setLowFrequency(value);
				break;
			case 0x4 :
				this->_managerChannelWave.setRestartOptions(value);
				break;
			default :
				break;
		}
	}


	//
	// channel Noise Reading and Writing
	//

	unsigned char APU::channelNoiseReading(unsigned short address) const
	{
		switch (address) {
			case 0x0 :
				return this->_managerChannelNoise.getSoundLength();
			case 0x1 :
				return this->_managerChannelNoise.getVolume();
			case 0x2 :
				return this->_managerChannelNoise.getPolynomialCounters();
			case 0x3 :
				return this->_managerChannelNoise.getRestartOptions();
			default :
				return 0xFF;
		}
	}

	void APU::channelNoiseWriting(unsigned short address, unsigned char value)
	{
		switch (address) {
			case 0x0 :
				this->_managerChannelNoise.setSoundLength(value);
				break;
			case 0x1 :
				this->_managerChannelNoise.setVolume(value);
				break;
			case 0x2 :
				this->_managerChannelNoise.setPolynomialCounters(value);
				break;
			case 0x3 :
				this->_managerChannelNoise.setRestartOptions(value);
				break;
			default :
				break;
		}
	}

	//
	//Controller Implementation
	//

	unsigned char APU::controllerReading(unsigned short address) const
	{
		switch (address) {
			case 0x0 :
				return getVin();
			case 0x1 :
				return getSOTS();
			case 0x2 :
				return getSoundOnOff();
			default :
				return 0xFF;
		}
	}

	void APU::controllerWriting(unsigned short address, unsigned char value)
	{
		switch (address) {
			case 0x0:
				setVin(value);
				break;
			case 0x1:
				setSOTS(value);
				break;
			case 0x2:
				setSoundOnOff(value);
				break;
			default:
				return;
		}
	}

	void APU::setVin(unsigned char value)
	{
		this->_VinToSo2 = value >> 7U;
		this->_SO2OutputLevel = (value & 0b01110000U) >> 4U;
		this->_VinToSo1 = (value & 0b00001000U) >> 3U;
		this->_SO1OutputLevel = (value & 0b00000111U);
		this->_managerChannel1.setSOTerminalsVolumes(    ((this->_soundOutputTerminalSelection & 0b00000001U) != 0) * this->_SO1OutputLevel, ((this->_soundOutputTerminalSelection & 0b00010000U) != 0) * this->_SO2OutputLevel);
		this->_managerChannel2.setSOTerminalsVolumes(    ((this->_soundOutputTerminalSelection & 0b00000010U) != 0) * this->_SO1OutputLevel, ((this->_soundOutputTerminalSelection & 0b00100000U) != 0) * this->_SO2OutputLevel);
		this->_managerChannelWave.setSOTerminalsVolumes( ((this->_soundOutputTerminalSelection & 0b00000100U) != 0) * this->_SO1OutputLevel, ((this->_soundOutputTerminalSelection & 0b01000000U) != 0) * this->_SO2OutputLevel);
		this->_managerChannelNoise.setSOTerminalsVolumes(((this->_soundOutputTerminalSelection & 0b00001000U) != 0) * this->_SO1OutputLevel, ((this->_soundOutputTerminalSelection & 0b10000000U) != 0) * this->_SO2OutputLevel);
	}

	unsigned char APU::getVin() const
	{
		unsigned char value = this->_VinToSo2;

		value <<= 3U;
		value |= this->_SO2OutputLevel;
		value <<= 1U;
		value |= this->_VinToSo1;
		value <<= 3U;
		return (value | this->_SO1OutputLevel);
	}

	void APU::setSOTS(unsigned char value)
	{
		this->_soundOutputTerminalSelection = value;
		this->_managerChannel1.setSOTerminalsVolumes(    ((value & 0b00000001U) != 0) * this->_SO1OutputLevel, ((value & 0b00010000U) != 0) * this->_SO2OutputLevel);
		this->_managerChannel2.setSOTerminalsVolumes(    ((value & 0b00000010U) != 0) * this->_SO1OutputLevel, ((value & 0b00100000U) != 0) * this->_SO2OutputLevel);
		this->_managerChannelWave.setSOTerminalsVolumes( ((value & 0b00000100U) != 0) * this->_SO1OutputLevel, ((value & 0b01000000U) != 0) * this->_SO2OutputLevel);
		this->_managerChannelNoise.setSOTerminalsVolumes(((value & 0b00001000U) != 0) * this->_SO1OutputLevel, ((value & 0b10000000U) != 0) * this->_SO2OutputLevel);
	}

	unsigned char APU::getSOTS() const
	{
		return (this->_soundOutputTerminalSelection);
	}

	void APU::setSoundOnOff(unsigned char value)
	{
		this->_allSoundsOn = value >> 7U;
		this->_managerChannel1.disable(!this->_allSoundsOn);
		this->_managerChannel2.disable(!this->_allSoundsOn);
		this->_managerChannelWave.disable(!this->_allSoundsOn);
		this->_managerChannelNoise.disable(!this->_allSoundsOn);
	}

	unsigned char APU::getSoundOnOff() const
	{
		unsigned char value = this->_allSoundsOn;

		value <<= 3U;
		value |= 0b00000111U;
		value <<= 1U;
		value |= this->_soundOnOffSound;
		value <<= 1U;
		value |= this->_soundOnOffWave;
		value <<= 1U;
		value |= this->_soundOnOff2;
		value <<= 1U;
		return (value | this->_soundOnOff1);
	}
}