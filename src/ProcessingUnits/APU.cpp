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

#define BASE_FREQU 1660

namespace GBEmulator
{
	std::vector<unsigned char> &getSquareWave(int frequency, float percentage)
	{
		static std::vector<unsigned char>	raw(44100LLU);

		for (int i = 0; i < 44100; i++)
			raw[i] = (std::fmod(i * frequency * 100 / 44100, 100) > percentage ? 127 : -127);
		return (raw);
	}

	APU::APU(ISound &channelOne, ISound &channelTwo, ISound &channelThree, ISound &channelFour) :
	_managerChannel1(channelOne),
	_managerChannel2(channelTwo),
	_managerChannelWave(channelThree),
	_managerChannelNoise(channelFour),
	_wpRAM(CHANSIZE_WPRAM, CHANSIZE_WPRAM)
	{
		channelOne.setWave(getSquareWave(BASE_FREQU, 50), 44100);
		channelTwo.setWave(getSquareWave(BASE_FREQU, 50), 44100);
	}

	APU::~APU() = default;

	void APU::Sound::disable(bool state)
	{
		this->_soundOn = !state && this->_restart;
		this->_soundChannel.setVolume(this->_soundOn * this->_initialVolume * 100.f / 15);
		this->_volumeCycles = 0;
	}

	void APU::Sound::updateRestart()
	{
		this->_soundOn = false;
		this->_restart = false;
		this->_volumeCycles = 0;
		this->disable(true);
	}

	void APU::Sound::update(unsigned cycle, Memory::Memory &memory)
	{
		if (!this->_soundOn && this->_restart) {
			this->_soundOn = true;
			this->_soundChannel.setVolume(this->_initialVolume * 100.f / 15);
		}
		if (!this->_soundOn)
			return;
		this->_volumeCycles += cycle;
		this->_sweepCycles += cycle;
		if (this->_isSixBitsLength) {
			if (this->_restartType &&
				this->_volumeCycles > Timing::getCyclesPerSecondsFromFrequency(256 / (64 - this->_soundLength))) {
				updateRestart();
			}
		} else {
			if (this->_restartType &&
				this->_volumeCycles > Timing::getCyclesPerSecondsFromFrequency(2 / (256 - this->_soundLength))) {
				updateRestart();
			}
		}
		if (this->_volumeShiftNumber) {
			int volume = (
					this->_volumeCycles / (this->_volumeShiftNumber * Timing::getCyclesPerSecondsFromFrequency(64)) *
					(this->_volumeDirection * 2 - 1) +
					this->_initialVolume
			);
			this->_soundChannel.setVolume((volume > 0 ? (volume > 15 ? 15 : volume) : 0) * 100.f / 15);
		}
		if (this->_sweepTime) {
			double newFrequency = (
					131072.f / (2048 - this->_frequency) +
					(this->_sweepCycles / Timing::getCyclesPerSecondsFromFrequency(this->_sweepShiftNumber / 128.)) *
					(131072.f / (2048 - this->_frequency) / pow(2, this->_sweepShiftNumber)) *
					((this->_sweepDirection - 1) * 2 + 1)
				);
			if (!this->_isSixBitsLength) {
				this->_soundChannel.setWave(getWavePattern(newFrequency, memory), 44100);
			}
			this->_soundChannel.setPitch(newFrequency / BASE_FREQU);
		}
		//pitchNoise
		if (this->_havingPolynomial) {
			this->_sweepCycles = 0;
			unsigned char stepNumber = this->_polynomialCounterStep ? 7 : 15;

			double frequency = pow(2, -(this->_shiftClockFrequency + 1)) *
				   dividingRatio[this->_dividingRatio];

			if (_wroteInNoiseFrequency) {
				std::cout << "_shiftClockFrequency : " << (int)_shiftClockFrequency << std::endl;
				std::cout << "_dividingRatio : " << (int)_dividingRatio << std::endl;
				std::cout << "frequency : " << frequency << std::endl;
				this->_soundChannel.setWave(getNoiseWave(frequency, stepNumber), 44100);
				this->_soundChannel.setPitch(BASE_FREQU);
				_wroteInNoiseFrequency = false;

			} else {
				updateLFSR(stepNumber);
			}
		}
	}

	std::vector<unsigned char> &APU::Sound::getWavePattern(int frequency, Memory::Memory &memory) const
	{
		static std::vector<unsigned char>	raw(44100LLU * 2);

		int shifting = _waveOutputLevel + 4 % 5;
		for (int i = 0; i < 44100; i++) {
			unsigned char wpRam = memory.read(WPRAM_START + (i % 16));
			raw[i*2] = (frequency / BASE_FREQU * (((wpRam >> 4) >> shifting) / 16 * 127));
			raw[i*2 + 1] = (frequency / BASE_FREQU * (((wpRam & 0b00001111) >> shifting) / 16 * 127));
		}
		return (raw);
	}

	/*std::vector<unsigned char> &APU::Sound::getNoiseWave(int frequency, unsigned char stepNumber)
	{
		static std::vector<unsigned char>	raw(44100LLU);

		for (int i = 0; i < 44100; i++) {
			//std::cout << (_lfsr & 0b1) << std::endl;
			raw[i] = ((rand() & 0b1) == 0 ? 127 : -127);
			//updateLFSR(stepNumber);
		}
		return (raw);
	}*/

	std::vector<unsigned char> &APU::Sound::getNoiseWave(int frequency, unsigned char stepNumber)
	{
		static std::vector<unsigned char>    raw(44100LLU);
		bool random = rand() & 0b1;
		int cnt = 0;

		for (int i = 0; i < 44100; i++) {
			raw[i] = (random == 0 ? 127 : -127);
			if (++cnt >= (44100 / frequency)) {
				random = rand() & 0b1;
				cnt = 0;
			}
		}
		return (raw);
	}

	void APU::Sound::updateLFSR(unsigned char stepNumber)
	{
		if (_counter == stepNumber) {
			unsigned short xorResult = ((((_lfsr & 0b10) >> 1) ^ (_lfsr & 0b1)) << 15) | 0b0111111111111111;
			_lfsr >>= 1;
			_lfsr &= xorResult;
			if (stepNumber == 7) {
				xorResult >>= 9;
				xorResult |= 0b1111111110000000;
				_lfsr &= xorResult;
			}
			//printf("LFSR : %i\n",_lfsr);*/
		}
		if (_counter > stepNumber)
			_counter = 0x0;
		_counter++;
	}

	void APU::update(unsigned cycle)
	{
		this->_managerChannel1.update(cycle, this->_wpRAM);
		this->_managerChannel2.update(cycle, this->_wpRAM);
		this->_managerChannelWave.update(cycle, this->_wpRAM);
		this->_managerChannelNoise.update(cycle, this->_wpRAM);
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
			/*case FF1A ... FF1E :
				channelWaveWriting(address - FF1A, value);
				break;*/
			case FF20 ... FF23 :
				channelNoiseWriting(address - FF20, value);
				break;
			case FF24 ... FF26 :
				controllerWriting(address - FF24, value);
				break;
			case WPRAM_START ... WPRAM_END :
				this->_wpRAM.write(address - WPRAM_START, value);
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
				return this->_wpRAM.read(address);
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
				this->_managerChannel1.setSweep(value);
				break;
			case 0x1 :
				this->_managerChannel1.setWave(value);
				break;
			case 0x2 :
				this->_managerChannel1.setVolume(value);
				break;
			case 0x3 :
				this->_managerChannel1.setLowFrequency(value);
				break;
			case 0x4 :
				this->_managerChannel1.setRestartOptions(value);
				break;
			default :
				break;

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
				this->_managerChannel2.setWave(value);
				break;
			case 0x1 :
				this->_managerChannel2.setVolume(value);
				break;
			case 0x2 :
				this->_managerChannel2.setLowFrequency(value);
				break;
			case 0x3 :
				this->_managerChannel2.setRestartOptions(value);
				break;
			default :
				break;

		}
	}

	//
	//ChannelWave Reading and Writing
	//

	unsigned char APU::channelWaveReading(unsigned short address) const
	{
		switch (address) {
			case 0x0 :
				return this->_managerChannelWave.getSoundONOFF();
			case 0x1 :
				return this->_managerChannelWave.getSoundLength(false);
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
				this->_managerChannelWave.setSoundONOFF(value);
				break;
			case 0x1 :
				this->_managerChannelWave.setSoundLength(value, false);
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
				return this->_managerChannelNoise.getSoundLength(true);
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
				this->_managerChannelNoise.setSoundLength(value, true);
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
	// General getter/Setters from SOUND
	//

	APU::Sound::Sound(ISound &sound) :
	_soundChannel(sound)
	{
	}

	void APU::Sound::setSweep(unsigned char value)
	{
		this->_volumeCycles = 0;
		this->_sweepTime = (value & 0b01110000) >> 4;
		this->_sweepDirection = (value & 0b00001000) >> 3;
		this->_sweepShiftNumber = (value & 0b00000111);
	}

	unsigned char APU::Sound::getSweep() const
	{
		unsigned char value = 0b00000001;

		value <<= 3;
		value |= this->_sweepTime;
		value <<= 1;
		value |= this->_sweepDirection;
		value <<= 3;
		return (value | this->_sweepShiftNumber);
	}

	void APU::Sound::setWave(unsigned char value)
	{
		this->_soundLength = value & 0b00111111;
		this->_volumeCycles = 0;
		if (this->_wavePattern != value >> 6) {
			this->_wavePattern = value >> 6;
			switch (this->_wavePattern) {
			case 0:
				this->_soundChannel.setWave(getSquareWave(BASE_FREQU, 12.5), 44100);
				break;
			case 1:
				this->_soundChannel.setWave(getSquareWave(BASE_FREQU, 25), 44100);
				break;
			case 2:
				this->_soundChannel.setWave(getSquareWave(BASE_FREQU, 50), 44100);
				break;
			case 3:
				this->_soundChannel.setWave(getSquareWave(BASE_FREQU, 75), 44100);
				break;
			default:
				return;
			}
		}
	}

	unsigned char APU::Sound::getWave() const
	{
		unsigned char value = this->_wavePattern;

		value <<= 6;
		return (value | 0b00111111);
	}

	void APU::Sound::setVolume(unsigned char value)
	{
		this->_initialVolume = value >> 4;
		this->_volumeDirection = (value & 0b00001000) >> 3;
		this->_volumeShiftNumber = value & 0b00000111;
		this->_volumeCycles = 0;
		if (this->_soundOn)
			this->_soundChannel.setVolume(this->_initialVolume * 100.f / 15);
	}

	unsigned char APU::Sound::getVolume() const
	{
		unsigned char value = this->_initialVolume;

		value <<= 1;
		value |= this->_volumeDirection;
		value <<= 3;
		return (value | this->_volumeShiftNumber);
	}

	void APU::Sound::setLowFrequency(unsigned char value)
	{
		this->_frequency = (this->_frequency & 0b11100000000) | value;
		this->_volumeCycles = 0;
		this->_soundChannel.setPitch(131072.f / (2048 - this->_frequency) / BASE_FREQU);
	}

	void APU::Sound::setRestartOptions(unsigned char value)
	{
		unsigned short val = value & 0b00000111;

		val <<= 8;
		this->_restart = value >> 7;
		this->_restartType = (value & 0b01000000) >> 6;
		this->_volumeCycles = 0;
		this->_frequency = (this->_frequency & 0b00011111111) | val;
		this->_soundChannel.setPitch(131072.f / (2048 - this->_frequency) / BASE_FREQU);
	}

	unsigned char APU::Sound::getRestartOptions() const
	{
		unsigned char value = 0b00000001;

		value <<= 1;
		value |= this->_restartType;
		value <<= 6;
		return (value | 0b00111111);
	}

	//
	// Wave Functions Implementation
	//

	void APU::Sound::setSoundONOFF(unsigned char value)
	{
		this->_soundOn = value >> 7;
		this->_volumeCycles = 0;
		if (!this->_soundOn)
			this->_soundChannel.setVolume(0);
		else
			this->_soundChannel.setVolume(this->_initialVolume * 100.f / 15);
	}

	unsigned char APU::Sound::getSoundONOFF() const
	{
		unsigned char value = this->_soundOn;

		value <<= 7;
		return (value | 0b01111111);
	}

	void APU::Sound::setSoundLength(unsigned char value, bool sixBitsLength)
	{
		this->_volumeCycles = 0;
		if (!sixBitsLength) {
			this->_isSixBitsLength = false;
			this->_soundLength = value;
		} else
			this->_soundLength = value & 0b00111111;
	}

	unsigned char APU::Sound::getSoundLength(bool sixBitsLength) const
	{
		if (!sixBitsLength)
			return (this->_soundLength);
		else
			return (0b11000000 | this->_soundLength);
	}

	void APU::Sound::setOutputLevel(unsigned char value)
	{
		this->_waveOutputLevel = (value & 0b10011111) >> 5;
	}

	unsigned char APU::Sound::getOutputLevel() const
	{
		unsigned char value = 0b00000001;

		value <<= 2;
		value |= this->_waveOutputLevel;
		value <<= 5;
		return (value | 0b00011111);
	}

	//
	// Noise Functions Implementation
	//

	void APU::Sound::setPolynomialCounters(unsigned char value)
	{
		//printf("oui\n");
		this->_havingPolynomial = true;
		this->_wroteInNoiseFrequency = true;
		this->_shiftClockFrequency = value >> 4;
		this->_polynomialCounterStep = (value & 0b00001000) >> 3;
		this->_dividingRatio = value & 0b00000111;

	}

	unsigned char APU::Sound::getPolynomialCounters() const
	{
		unsigned char value = this->_shiftClockFrequency;

		value <<= 1;
		value |= this->_polynomialCounterStep;
		value <<= 3;
		return (value | this->_dividingRatio);
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
		this->_VinToSo2 = value >> 7;
		this->_SO2OutputLevel = (value & 0b01110000) >> 4;
		this->_VinToSo1 = (value & 0b00001000) >> 3;
		this->_SO1OutputLevel = (value & 0b00000111);
	}

	unsigned char APU::getVin() const
	{
		unsigned char value = this->_VinToSo2;

		value <<= 3;
		value |= this->_SO2OutputLevel;
		value <<= 1;
		value |= this->_VinToSo1;
		value <<= 3;
		return (value | this->_SO1OutputLevel);
	}

	void APU::setSOTS(unsigned char value)
	{
		this->_soundOutputTerminalSelection = value;
	}

	unsigned char APU::getSOTS() const
	{
		return (this->_soundOutputTerminalSelection);
	}

	void APU::setSoundOnOff(unsigned char value)
	{
		this->_allSoundsOn = value >> 7;
		this->_managerChannel1.disable(!this->_allSoundsOn);
		this->_managerChannel2.disable(!this->_allSoundsOn);
		this->_managerChannelWave.disable(!this->_allSoundsOn);
		this->_managerChannelNoise.disable(!this->_allSoundsOn);
	}

	unsigned char APU::getSoundOnOff() const
	{
		unsigned char value = this->_allSoundsOn;

		value <<= 3;
		value |= 0b00000111;
		value <<= 1;
		value |= this->_soundOnOff1;
		value <<= 1;
		value |= this->_soundOnOff2;
		value <<= 1;
		value |= this->_soundOnOffWave;
		value <<= 1;
		return (value | this->_soundOnOffSound);
	}
}