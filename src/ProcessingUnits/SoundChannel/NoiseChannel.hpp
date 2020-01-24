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
	//! @brief Class représentant le "Channel 3"
	class NoiseChannel : public SoundChannel {
	private:
		//! @brief Les 4 formes d'ondes qui peuvent être jouées
		std::vector<std::vector<unsigned char>> _waves;
		//! @brief Le ratio de division du bruit.
		unsigned char _dividingRatio = 0;
		//! @brief Whether the noise wave needs to be updated.
		bool _wroteInNoiseFrequency = false;
		//! @brief La fréquence de l'horloge.
		unsigned char _shiftClockFrequency = 0;
		//! @brief Compteur d'étape.
		bool _polynomialCounterStep = false;
		//! @brief L'état du LFSR.
		unsigned short _lfsr = 0;
		//! @brief Période dans l'onde.
		double _bitPeriod = 0;

		//! @brief Met à jour le LFSR.
		void _updateLFSR(unsigned char stepNumber, std::vector<unsigned char> &lfsrBit);
		//! @brief Met à jour le canal.
		//! @param cycles Nombre de cycles passés (non utilisé)
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
