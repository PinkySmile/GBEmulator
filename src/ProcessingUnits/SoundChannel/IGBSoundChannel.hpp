//
// Created by andgel on 04/05/2021
//

#ifndef GBEMULATOR_IGBSOUNDCHANNEL_HPP
#define GBEMULATOR_IGBSOUNDCHANNEL_HPP


#define SAMPLE_RATE 44100
#include <vector>

namespace GBEmulator
{
	class IGBSoundChannel {
	public:
		virtual void write(unsigned int relativeAddress, unsigned char value) = 0;
		virtual unsigned char read(unsigned int relativeAddress) = 0;
		virtual std::vector<short> update(unsigned int cycles) = 0;
		virtual bool hasExpired() const = 0;
	};
}


#endif //GBEMULATOR_IGBSOUNDCHANNEL_HPP
