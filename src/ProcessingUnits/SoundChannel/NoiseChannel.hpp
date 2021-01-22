/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** NoiseChannel.hpp
*/

#ifndef GBEMULATOR_NOISECHANNEL_HPP
#define GBEMULATOR_NOISECHANNEL_HPP


#include "SoundChannel.hpp"

/*!
 * @brief Fréquence de base utilisé pour confectionné le noise.
 * Il est par la suite divisé pour obtenir la fréquence réel du son joué.
 */
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
		void _update(unsigned cycles) override;

		/*!
		 * @brief Ratio de division de la fréquence.
		 * Fréquence utilisé pour confectionné la fréquence du son joué dans le channel noise.
		 */
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
		/*!
		 * @brief Permet de créer la wave du noise.
		 * @param stepNumber Mode 7 ou 15 bits
		 * @return la nouvelle wave pour le noise
		 */
		std::vector<unsigned char> getNoiseWave(unsigned char stepNumber);
		//! @brief Constructeur.
		//! @param soundInterface L'interface utilisé pour jouer le son.
		NoiseChannel(ISound &soundInterface);

		/*!
		 * @brief Permet de changer la longueur du son joué dans le channel noise.
		 * @param length Longueur du son (6 bits)
		 */
		void setSoundLength(unsigned char length);
		/*!
		 * @brief Permet de changer les attributs de modification de fréquence du son joué.
		 * @param value Byte contenant les valeurs pour le nouveau son joué.
		 */
		void setPolynomialCounters(unsigned char value);
		/*!
		 * @brief Permet de récupérer le byte contenant les attributs de modificaitons de fréquence du son joué.
		 * @return Le byte contenant les attributs
		 */
		unsigned char getPolynomialCounters() const;
	};
}


#endif //GBEMULATOR_NOISECHANNEL_HPP
