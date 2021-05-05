//
// Created by andgel on 04/05/2021
//

#ifndef GBEMULATOR_BASICSOUNDCHANNEL_HPP
#define GBEMULATOR_BASICSOUNDCHANNEL_HPP


#include "IGBSoundChannel.hpp"

namespace GBEmulator
{
	class BasicSoundChannel : public IGBSoundChannel {
	private:
		unsigned _cycles = 0;

		virtual void _update(unsigned cycles) {};
		virtual short _getSoundData() const { return 0; };
	public:
		bool hasExpired() const override { return false; };
		void write(unsigned int relativeAddress, unsigned char value) override;
		unsigned char read(unsigned int relativeAddress) override;
		std::vector<short> update(unsigned int cycles) override;
	};
}


#endif //GBEMULATOR_BASICSOUNDCHANNEL_HPP
