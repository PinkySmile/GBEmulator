//
// Created by andgel on 03/06/2021
//

#include <wiringPi.h>
#include <softPwm.h>
#include "RaspberrySoundPlayer.hpp"

#define SPEAKER_PIN 18

namespace GBEmulator
{
	RaspberrySoundPlayer::RaspberrySoundPlayer()
	{
		pinMode(SPEAKER_PIN, OUTPUT);
		softPwmCreate(SPEAKER_PIN, 0, UINT16_MAX);
	}

	RaspberrySoundPlayer::~RaspberrySoundPlayer()
	{
	}

	void RaspberrySoundPlayer::setVolume(float volume)
	{
		this->_masterVolume = volume;
	}

	void RaspberrySoundPlayer::pushSamples(int16_t *samples, size_t)
	{
		softPwmWrite(SPEAKER_PIN, *samples - INT16_MIN);
	}
}