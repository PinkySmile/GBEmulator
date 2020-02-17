/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** CableInterface.hpp
*/

#ifndef GBEMULATOR_CABLEINTERFACE_HPP
#define GBEMULATOR_CABLEINTERFACE_HPP

namespace GBEmulator::Network
{
	//! @brief L'interface émulant le CableLink.
	//! Pour plus d'inforamtions: http://problemkaputt.de/pandocs.htm#serialdatatransferlinkcable
	class CableInterface {
	private:
		//! @brief Syncronise l'émulateur avec la console distante.
		//! @param cycles Le nombre de cycles CPU qui se sont écoulés.
		//! @note Cette fonction peut bloquer si l'émulateur est en avance par rapport à la console distante.
		virtual void _sync(unsigned cycles) = 0;

		//! @brief Envoie un byte de donnée.
		//! @param byte Le byte qui doit être envoyé.
		virtual void _sendByte(unsigned char byte) = 0;

	protected:
		//! @brief Est-ce qu'une interruption doit être envoyé.
		bool _needInterrupt = false;
		//! @brief Est-ce que l'horloge utilisée est celle de la console distante.
		bool _isExternal = true;
		//! @brief Est-ce qu'un transfert est actif.
		bool _isTransfering = false;

	public:
		//! @brief Le byte utilisé pour l'I/O ($FF01)
		unsigned char byte = 0x00;

		//! @brief Change le byte de controle.
		//! @param c_byte Le nouveau byte de controle
		//! @details
		//! Bit 7 - Transfert démarré (0=Pas de transfert, 1=Transfert en cours)
		//! Bit 0 - Horloge utilisée (0=Horloge externe, 1=Horloge interne)
		void setControlByte(unsigned char c_byte);

		//! @brief Construit le byte de controle.
		//! @return Le byte de controle.
		//! @details
		//! Bit 7 - Transfert démarré (0=Pas de transfert, 1=Transfert en cours)
		//! Bit 0 - Horloge utilisée (0=Horloge externe, 1=Horloge interne)
		unsigned char getControlByte() const;

		//! @brief Est-ce que l'horloge utilisée est celle de la console distante.
		//! @return false si l'horloge utilisée est l'horloge interne. Sinon, true.
		bool isExternal() const;

		//! @brief Est-ce qu'une interruption à été déclanchées.
		bool triggerInterrupt();

		//! @brief Est-ce que le transfert est toujours en cours.
		//! @return true si un transfert en cours. Sinon, false.
		bool isTransfering() const;

		//! @brief Met à jour l'état de l'interface.
		//! @param cycles Le nombre de cycles CPU écoulés.
		void update(unsigned int cycles);

		//! @brief Active le transfert.
		void transfer();
	};
}

#endif //GBEMULATOR_CABLEINTERFACE_HPP
