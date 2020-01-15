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
		//! @brief Change the wave duty.
		void setWave(unsigned char value);
		//! @brief Get the wave duty.
		unsigned char getWave() const;
	};
}


#endif //GBEMULATOR_SQUAREWAVECHANNEL_HPP
