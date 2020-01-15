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
		//! @breif All 4 wave forms that can be played
		std::vector<std::vector<unsigned char>> _waves;
		//! @breif The current wave form played.
		unsigned char _wavePattern = 0;

		void _update(unsigned cycles) override;

	public:

		//! @brief Returns a square shaped wave;
		static std::vector<unsigned char> &getSquareWave(int frequency, float percentage);

		//! @brief Constructor.
		//! @param soundInterface The interface to output the sound to.
		SquareWaveChannel(ISound &soundInterface);
		void write(unsigned char address, unsigned char value) override;
		unsigned char read(unsigned char address) const override;
		void restart() override;

		void setWave(unsigned char value);
		unsigned char getWave() const;
	};
}


#endif //GBEMULATOR_SQUAREWAVECHANNEL_HPP
