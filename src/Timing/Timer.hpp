/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Timer.hpp
*/

#ifndef GBEMULATOR_TIMER_HPP
#define GBEMULATOR_TIMER_HPP


#ifdef ARDUINO
#include <stdint.h>
#else
#include <cstdint>
#endif

#define GB_CPU_FREQUENCY 4194304

namespace GBEmulator::Timing
{
	//! @brief Transforme une fréquence en nombre de cycles CPU.
	//! @param frequency Fréquence à transformer en cycles CPU
	inline double getCyclesPerSecondsFromFrequency(double frequency)
	{
		return GB_CPU_FREQUENCY / frequency;
	}

	//! @brief Classe implémentant le Timer de la GameBoy
	//! Pour plus d'informations : http://problemkaputt.de/pandocs.htm#timeranddividerregisters
	class Timer {
	private:
		//! @brief Octet de contrôle du timer.
		uint8_t _byte = 0;
		//! @brief Octet de compte pour le timer.
		uint8_t _counter = 0;
		//! @brief Nombre de cycles du timer.
		double _cycles = 0;
		//! @brief Nombre de cycles attendus par le timer.
		double _expected;

	public:
		//! @brief Création de la classe timer : Initialise _expected par le nombre de cycles attendus.
		Timer();
		//! @brief Modulo du timer.
		uint8_t modulo = 0;

		/*! @brief Retourne un booléen pour savoir si le timer est activé ou non
		 *  @returns L'état du timer : True -> En marche / False -> A l'arrêt
		 */
		bool isActivated() const;
		/*! @brief Retourne la fréquence passée en entrée du registre du Timer Control
		 * @return La fréquence en Hertz en fonction des bits 1 et 0 de l'input clock du Timer Control
		 */
		unsigned long getFrequency() const;
		//! @brief Retourne l'octet Timer Control
		//!@return La valeur de l'octet Timer Control
		//! @details
		//! Bit 2    - Timer Stop  (0=Arrêté, 1=Démarré)
		//! Bits 1-0 - Fréquence de l'horloge
		//!           00:   4096 Hz    (~4194 Hz SGB)
		//!           01: 262144 Hz  (~268400 Hz SGB)
		//!           10:  65536 Hz   (~67110 Hz SGB)
		//!           11:  16384 Hz   (~16780 Hz SGB)
		uint8_t getControlByte() const;
		//! @brief Retourne le compteur du Timer Counter
		//! @return La valeur de l'octet Timer Counter
		uint8_t getCounter() const;

		/*! @brief Permet de renseigner la nouvelle valeur dans _counter.
		 * @param byte Nouvelle valeur du _counter.
		 */
		void setCounter(uint8_t byte);
		//! @brief Permet de renseigner la nouvelle valeur dans _byte.
		//!@param byte Nouvelle valeur du _byte.
		//! @details
		//! Bit 2    - Timer Stop  (0=Arrêté, 1=Démarré)
		//! Bits 1-0 - Fréquence de l'horloge
		//!           00:   4096 Hz    (~4194 Hz SGB)
		//!           01: 262144 Hz  (~268400 Hz SGB)
		//!           10:  65536 Hz   (~67110 Hz SGB)
		//!           11:  16384 Hz   (~16780 Hz SGB)
		void setControlByte(uint8_t byte);
		/*!@brief Permet de mettre à jour _cycles et _counter.
		 * @param cycles Le nombre de cycles CPU écoulés
		 * @return Si le counter tombe à 0, retourne True, sinon False.
		 */
		bool update(unsigned cycles);
	};
}


#endif //GBEMULATOR_TIMER_HPP
