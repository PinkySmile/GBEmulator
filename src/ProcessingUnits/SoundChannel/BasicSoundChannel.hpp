//
// Created by andgel on 04/05/2021
//

#ifndef GBEMULATOR_BASICSOUNDCHANNEL_HPP
#define GBEMULATOR_BASICSOUNDCHANNEL_HPP


#include "IGBSoundChannel.hpp"
#define SOUND_VALUE 8160

namespace GBEmulator
{
	class BasicSoundChannel : public IGBSoundChannel {
	private:
		unsigned _cycles = 0;

		virtual void _update(unsigned cycles) = 0;
		virtual int16_t _getSoundData() const = 0;

	protected:
		bool _expired = true;

	public:
		bool hasExpired() const override final { return this->_expired; };
		standard::vector<int16_t> update(unsigned int cycles) override;
	};
}


#endif //GBEMULATOR_BASICSOUNDCHANNEL_HPP
