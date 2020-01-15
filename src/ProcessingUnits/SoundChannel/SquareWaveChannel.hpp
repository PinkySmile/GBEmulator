/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SquareWaveChannel.hpp
*/

#ifndef GBEMULATOR_SQUAREWAVECHANNEL_HPP
#define GBEMULATOR_SQUAREWAVECHANNEL_HPP


#include "SoundChannel.hpp"

namespace GBEmulator::SoundChannel
{
	class SquareWaveChannel : public SoundChannel {
	private:
		unsigned char _wavePattern = 0;
		unsigned char _soundLength = 0;

		void _setWave(unsigned char value);
		unsigned char _getWave();

	public:
		static std::vector<unsigned char> &getSquareWave(int frequency, float percentage);
		//! @brief Constructor.
		//! @param soundInterface The interface to output the sound to.
		SquareWaveChannel(ISound &soundInterface);
		void write(unsigned char address, unsigned char value) override;
		unsigned char read(unsigned char address) override;
		void update(unsigned cycles) override;
		void restart() override;
	};
}


#endif //GBEMULATOR_SQUAREWAVECHANNEL_HPP
