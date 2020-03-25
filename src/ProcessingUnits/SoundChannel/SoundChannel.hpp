/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SoundChannel.hpp
*/

#ifndef GBEMULATOR_SOUNDCHANNEL_HPP
#define GBEMULATOR_SOUNDCHANNEL_HPP

#include "../../Sound/ISound.hpp"

#define BASE_FREQU (440)

namespace GBEmulator::SoundChannel
{
	//! @brief Représente un canal de son.
	//! Pour plus d'information: http://problemkaputt.de/pandocs.htm#soundcontroller.
	class SoundChannel {
	protected:
		enum Direction
		{
			DECREASE,
			INCREASE
		};

		//State
		//! @brief L'interface utilisé pour la sortie son
		ISound &_sound;
		//! @brief Octets de fréquence actuels de ce canal.
		unsigned short _frequency = 0;
		bool _restart = false;
		//! @brief Si ce canal ne boucle pas.
		bool _restartType = false;
		//! @brief Si le son est activé.
		bool _soundOn = false;
		//! @brief La longeur du son.
		unsigned char _soundLength = 0;

		//Sweep
		//! @brief Le temps restant avant le balayage.
		unsigned char _sweepTime = 0;
		//! @brief La vitesse du balayage.
		unsigned char _sweepShiftNumber = 0;
		//! @brief La direction du balayage.
		Direction _sweepDirection = INCREASE;
		//! @brief Nombre de cycles CPU écoulés depuis le début du balayage.
		double _sweepCycles = 0;
		unsigned char _shiftRemain = 0;
		double _realFrequency = 0;


		//Volume
		//! @brief Le volume initial de l'enveloppe.
		unsigned char _initialVolume = 0;
		//! @brief La direction de l'enveloppe.
		Direction _volumeDirection = DECREASE;
		//! @brief La vitesse de l'enveloppe de volume.
		unsigned char _volumeShiftNumber = 0;
		//! @brief Nombre de cycles CPU écoulés depuis le début de l'enveloppe.
		unsigned _volumeCycles = 0;

		//! @brief Met à jour le canal.
		//! @param Le nombre de cycles CPU écoulés.
		virtual void _update(unsigned cycles) = 0;

		/*!
		 * @brief Permet de mettre à jour le volume d'un son.
		 * @param cycles Le nombre de cycles CPU écoulés.
		 */
		void _updateVolume(unsigned cycles);
		/*!
		 * @brief Permet de mettre à jour la fréquence (le balayage de la fréquence) d'un son.
		 * @param cycles Le nombre de cycles CPU écoulés.
		 */
		void _updateSweep(unsigned cycles);
		/*!
		 * @brief Permet de regarder si le son doit être rejoué ou arrêté.
		 */
		virtual void _checkRestart();

	public:
		//! @brief Constructeur.
		//! @param soundInterface L'interface de sortie du son vers.
		SoundChannel(ISound &soundInterface);

		/*!
		 * @brief Permet de changer le balayage de fréquence d'un son joué.
		 * @param sweep Le byte de balayage de la fréquence.
		 */
		void setSweep(unsigned char sweep);
		/*!
		 * @brief Permet de changer le balayage de volume d'un son joué.
		 * @param sweep Le byte de balayage de volume.
		 */
		void setVolume(unsigned char volume);
		/*!
		 * @brief Permet de changer la fréquence basse du son joué.
		 * @param frequency Fréquence sur 8 bits.
		 */
		virtual void setLowFrequency(unsigned char frequency);
		/*!
		 * @brief Permet de changer les options pour rejouer le son, ainsi que les trois bits de fréquence haute.
		 * @param byte Octet du registre Restart Options.
		 */
		virtual void setRestartOptions(unsigned char byte);
		/*!
		 * @brief Permet de changer les volumes des sorties sons SO1 et SO2 de volume.
		 * @param SO1 Volume de la sortie son SO1.
		 * @param SO2 Volume de la sortie son SO2.
		 */
		void setSOTerminalsVolumes(unsigned char SO1, unsigned char SO2);
		/*!
		 * @brief Permet d'arrêter le son ou de reprendre le son.
		 * @param disabled True -> Arrêter, False -> Reprendre.
		 */
		void disable(bool disabled);

		/*!
		 * @brief Permet de récupérer le byte de balayage de fréquence.
		 * @return Le byte de balayage de fréquence.
		 */
		unsigned char getSweep() const;
		/*!
		 * @brief Permet de récupérer le byte de balayage de volume.
		 * @return Le byte de balayage de volume.
		 */
		unsigned char getVolume() const;
		/*!
		 * @brief Permet de récupérer le byte des options pour rejouer le son.
		 * @return Le byte contenant les informations pour rejouer le son.
		 */
		unsigned char getRestartOptions() const;

		//! @brief Met à jour le canal.
		//! @param Le nombre de cycles CPU écoulés.
		void update(unsigned cycles);
	};
}


#endif //GBEMULATOR_SOUNDCHANNEL_HPP
