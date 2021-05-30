//
// Created by andgel on 04/05/2021
//

#ifndef GBEMULATOR_IGBSOUNDCHANNEL_HPP
#define GBEMULATOR_IGBSOUNDCHANNEL_HPP


#define SAMPLE_RATE 44100
#ifndef ARDUINO
#include <vector>
#include <cstdint>
#else
#include "../../ArduinoStuff/FakeSTL.hpp"
#include <stdint.h>
#endif

namespace GBEmulator
{
	class IGBSoundChannel {
	public:
		virtual void write(unsigned int relativeAddress, uint8_t value) = 0;
		virtual unsigned char read(unsigned int relativeAddress) = 0;
		virtual standard::vector<uint16_t> update(unsigned int cycles) = 0;
		virtual bool hasExpired() const = 0;
		virtual void onPowerOff() = 0;
	};
}


#endif //GBEMULATOR_IGBSOUNDCHANNEL_HPP
