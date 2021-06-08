//
// Created by andgel on 03/06/2021
//

#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include "RaspberrySoundPlayer.hpp"

#define SPEAKER_PIN 18

namespace GBEmulator
{
	RaspberrySoundPlayer::RaspberrySoundPlayer()
	{
		pinMode(SPEAKER_PIN, OUTPUT);
		softPwmCreate(SPEAKER_PIN, 0, UINT16_MAX);
		this->_thread = std::thread{[this]{
			return;
			while (true) {
				if (!this->_buffer.empty()) {
					softPwmWrite(SPEAKER_PIN, this->_buffer[this->_head] - INT16_MIN);
					this->_head = (this->_head + 1) % this->_buffer.size();
				}
				std::this_thread::sleep_for(std::chrono::microseconds(1000000 / SAMPLE_RATE));
			}
		}};
	}

	RaspberrySoundPlayer::~RaspberrySoundPlayer()
	{
	}

	void RaspberrySoundPlayer::setVolume(float volume)
	{
		this->_masterVolume = volume;
	}

	void RaspberrySoundPlayer::pushSamples(int16_t *samples, size_t size)
	{
		this->_buffer = std::vector<int16_t>{samples, samples + size};
	}
}
