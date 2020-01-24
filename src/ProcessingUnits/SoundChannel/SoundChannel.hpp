/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SoundChannel.hpp
*/

#ifndef GBEMULATOR_SOUNDCHANNEL_HPP
#define GBEMULATOR_SOUNDCHANNEL_HPP

#include "../../Sound/ISound.hpp"

#define BASE_FREQU (1760)

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

		void _updateVolume(unsigned cycles);
		void _updateSweep(unsigned cycles);
		virtual void _checkRestart();

	public:
		//! @brief Constructeur.
		//! @param soundInterface L'interface de sortie du son vers.
		SoundChannel(ISound &soundInterface);

		void setSweep(unsigned char);
		void setVolume(unsigned char);
		void setLowFrequency(unsigned char);
		void setRestartOptions(unsigned char);
		void setSOTerminalsVolumes(unsigned char SO1, unsigned char SO2);
		void disable(bool disabled);

		unsigned char getSweep() const;
		unsigned char getVolume() const;
		unsigned char getRestartOptions() const;

		//! @brief Met à jour le canal.
		//! @param Le nombre de cycles CPU écoulés.
		void update(unsigned cycles);
	};
}


#endif //GBEMULATOR_SOUNDCHANNEL_HPP
