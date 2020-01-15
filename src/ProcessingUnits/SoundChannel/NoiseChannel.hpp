/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** NoiseChannel.hpp
*/

#ifndef GBEMULATOR_NOISECHANNEL_HPP
#define GBEMULATOR_NOISECHANNEL_HPP


#include "SoundChannel.hpp"

#define DIV_FREQUENCY 4194304

namespace GBEmulator::SoundChannel
{
	class NoiseChannel : public SoundChannel {
	private:
		//! @breif All 4 wave forms that can be played
		std::vector<std::vector<unsigned char>> _waves;
		unsigned char _dividingRatio = 0;
		bool _wroteInNoiseFrequency = false;
		unsigned char _shiftClockFrequency = 0;
		bool _polynomialCounterStep = false;
		unsigned short _lfsr = 0;
		double _bitPeriod = 0;

		void _updateLFSR(unsigned char stepNumber, std::vector<unsigned char> &lfsrBit);
		void _update(unsigned cycles) override;

		static constexpr double dividingRatio[8] = {
			4. / DIV_FREQUENCY,
			8. / DIV_FREQUENCY,
			16. / DIV_FREQUENCY,
			24. / DIV_FREQUENCY,
			32. / DIV_FREQUENCY,
			40. / DIV_FREQUENCY,
			48. / DIV_FREQUENCY,
			56. / DIV_FREQUENCY
		};

	public:
		std::vector<unsigned char> getNoiseWave(unsigned char stepNumber);
		//! @brief Constructor.
		//! @param soundInterface The interface to output the sound to.
		NoiseChannel(ISound &soundInterface);

		void setSoundLength(unsigned char);
		void setPolynomialCounters(unsigned char);
		unsigned char getSoundLength() const;
		unsigned char getPolynomialCounters() const;
	};
}


#endif //GBEMULATOR_NOISECHANNEL_HPP
