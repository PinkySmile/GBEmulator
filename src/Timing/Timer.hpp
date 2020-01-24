/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Timer.hpp
*/

#ifndef GBEMULATOR_TIMER_HPP
#define GBEMULATOR_TIMER_HPP


#define GB_CPU_FREQUENCY 4194304

namespace GBEmulator::Timing
{
	//! @brief Transforme une fréquence en nombre de cycles CPU.
	//! @param frequency Fréquence à transformer en cycles CPU
	double getCyclesPerSecondsFromFrequency(double frequency);

	//! @brief Classe implémentant le Timer de la GameBoy
	//! Pour plus d'informations : http://problemkaputt.de/pandocs.htm#timeranddividerregisters
	class Timer {
	private:
		//! @brief Octet de contrôle du timer.
		unsigned char _byte = 0;
		//! @brief Octet de compte pour le timer.
		unsigned char _counter = 0;
		//! @brief Nombre de cycles du timer.
		double _cycles = 0;
		//! @brief Nombre de cycles attendus par le timer.
		double _expected;

	public:
		//! @brief Création de la classe timer : Initialise _expected par le nombre de cycles attendus.
		Timer();
		//! @brief Modulo du timer.
		unsigned char modulo = 0;

		/*! @brief Retourne un booléen pour savoir si le timer est activé ou non
		 *  @returns L'état du timer : True -> En marche / False -> A l'arrêt
		 */
		bool isActivated() const;
		/*! @brief Retourne la fréquence passée en entrée du registre du Timer Control
		 * @return La fréquence en Hertz en fonction des bits 1 et 0 de l'input clock du Timer Control
		 */
		unsigned getFrequency() const;
		/*! @brief Retourne l'octet Timer Control
		 * @return La valeur de l'octet Timer Control
		 */
		unsigned char getControlByte() const;
		/*! @brief Retourne le compteur du Timer Counter
		 * @return La valeur de l'octet Timer Counter
		 */
		unsigned char getCounter() const;

		/*! @brief Permet de renseigner la nouvelle valeur dans _counter.
		 * @param byte Nouvelle valeur du _counter.
		 */
		void setCounter(unsigned char byte);
		/*! @brief Permet de renseigner la nouvelle valeur dans _byte.
		 *
		 * @param byte Nouvelle valeur du _byte.
		 */
		void setControlByte(unsigned char byte);
		/*!@brief Permet de mettre à jour _cycles et _counter.
		 *
		 * @param cycles Le nombre de cycles actuel
		 * @return Si le counter tombe à 0, retourne True, sinon False.
		 */
		bool update(unsigned cycles);
	};
}


#endif //GBEMULATOR_TIMER_HPP
