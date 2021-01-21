/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** NoiseChannel.cpp
*/

#include <cmath>
#include "NoiseChannel.hpp"

namespace GBEmulator::SoundChannel
{
	NoiseChannel::NoiseChannel(GBEmulator::ISound &soundInterface) :
		SoundChannel(soundInterface)
	{
	}

	std::vector<unsigned char> NoiseChannel::getNoiseWave(unsigned char stepNumber)
	{
		static std::vector<unsigned char>    raw(44100LLU);
		//bool random = rand() & 0b1;
		//int cnt = 0;
		double j = stepNumber == 7 ? 1 / _bitPeriod : ceil(_bitPeriod);
		std::vector<unsigned char> lfsrBit(stepNumber == 7 ? 127LLU : 32767LLU);

		this->_updateLFSR(stepNumber, lfsrBit);
		if (stepNumber == 7) {
			for (int i = 0; i < 2048; i++) {
				_lfsr += j;
				_lfsr %= 127;
				raw[i] = lfsrBit[_lfsr];
			}
		} else {
			for (int i = 0; i < 2048/*2048*/; i += j) {
				_lfsr++;
				_lfsr = _lfsr % 32767;
				float s = lfsrBit[_lfsr];
				for (int p = j; p--;)
					raw[i + p] = s;
			}
		}
		/*for (int i = 0; i < 44100; i++) {
			raw[i] = (random == 0 ? 127 : -127);
			if (++cnt >= (44100 / frequency)) {
				random = rand() & 0b1;
				cnt = 0;
			}
		}*/
		return (raw);
	}

	void NoiseChannel::_updateLFSR(unsigned char stepNumber, std::vector<unsigned char> &lfsrBit)
	{
		// precalculate LFSR patterns
		unsigned char start_state = 127;
		unsigned short LFSR = start_state;
		int st = 0;
		unsigned char bit = 0;

		do {
			bit = ((LFSR) ^ (LFSR >> 1)) & 0b1;
			LFSR = (LFSR >> 1) | (bit << (stepNumber - 1));
			lfsrBit[st++] = (bit ? 255 : 0);
		} while (LFSR != start_state);
		/*if (_counter == stepNumber) {
			unsigned short xorResult = ((((_lfsr & 0b10) >> 1) ^ (_lfsr & 0b1)) << 15) | 0b0111111111111111;
			_lfsr >>= 1;
			_lfsr &= xorResult;
			if (stepNumber == 7) {
				xorResult >>= 9;
				xorResult |= 0b1111111110000000;
				_lfsr &= xorResult;
			}
			//printf("LFSR : %i\n",_lfsr);
		}
		if (_counter > stepNumber)
			_counter = 0x0;
		_counter++;*/
	}

	void NoiseChannel::setSoundLength(unsigned char value)
	{
		this->_soundLength = value & 0b00111111U;
	}

	void NoiseChannel::setPolynomialCounters(unsigned char value)
	{
		this->_wroteInNoiseFrequency = true;
		this->_shiftClockFrequency = value >> 4U;
		this->_polynomialCounterStep = value & 0b00001000U;
		this->_dividingRatio = value & 0b00000111U;
	}

	unsigned char NoiseChannel::getSoundLength() const
	{
		return (0b11000000U | this->_soundLength);
	}

	unsigned char NoiseChannel::getPolynomialCounters() const
	{
		return (this->_shiftClockFrequency << 4U) | (this->_polynomialCounterStep << 3U) | this->_dividingRatio;
	}

	void NoiseChannel::_update(unsigned)
	{
		unsigned char stepNumber = this->_polynomialCounterStep ? 7 : 15;

		this->_bitPeriod = 44100 *
			std::pow(2, (this->_shiftClockFrequency + 1)) *
			dividingRatio[this->_dividingRatio];

		if (this->_wroteInNoiseFrequency) {
			this->_sound.setWave(getNoiseWave(stepNumber), 44100);
			this->_wroteInNoiseFrequency = false;
		}
	}
}