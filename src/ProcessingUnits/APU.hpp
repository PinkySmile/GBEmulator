/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.hpp
*/

#ifndef GBEMULATOR_APU_HPP
#define GBEMULATOR_APU_HPP

#define DIV_FREQUENCY 4194304

#include "../Memory/Memory.hpp"
#include "../Sound/ISound.hpp"
#include "SoundChannel/SoundChannel.hpp"
#include "SoundChannel/SquareWaveChannel.hpp"
#include "SoundChannel/NoiseChannel.hpp"
#include "SoundChannel/ModulableWaveChannel.hpp"

namespace GBEmulator
{
	/*!
	 * @brief Liste des adresses que le CPU peut envoyer à l'APU.
	 * Acutellement, n'utilise qu'une partie des adresses.
	 */
	enum regist {
		FF10 = 0x0,
		FF11 = 0x1,
		FF12 = 0x2,
		FF13 = 0x3,
		FF14 = 0x4,
		FF16 = 0x6,
		FF17 = 0x7,
		FF18 = 0x8,
		FF19 = 0x9,
		FF1A = 0xA,
		FF1B = 0xB,
		FF1C = 0xC,
		FF1D = 0xD,
		FF1E = 0xE,
		FF20 = 0x10,
		FF21 = 0x11,
		FF22 = 0x12,
		FF23 = 0x13,
		FF24 = 0x14,
		FF25 = 0x15,
		FF26 = 0x16,
		WPRAM_START = 0x20,
		WPRAM_END = 0x2F
	};
	/*!
	 * @brief Classe gérant l'audio de la GameBoy. La classe utilise les classes :
	 * - ModulableWaveChannel
	 * - NoiseChannel
	 * - SoundChannel
	 * - SquareWaveChannel
	 */
	class APU {
	public:
		/*!
		 * @brief Constructeur de la classe APU. Initialise la classe APU avec la création des quatres channels de son.
		 * @param channelOne Interface ISound permettant la création du channel 1.
		 * @param channelTwo Interface ISound permettant la créationdu channel 2.
		 * @param channelThree Interface ISound permettant la création du channel Wave.
		 * @param channelFour  Interface ISound permettant la création du channel Noise.
		 */
		APU(ISound &channelOne, ISound &channelTwo, ISound &channelThree, ISound &channelFour);

		/*!
		 * @brief La fonction write permet d'écrire des données dans un des quatres channels de l'APU.
		 * @param address Adresse d'écriture dans le channel. (Les valeurs sont légèrement modifiés de l'original, voir l'enumération regist pour plus d'informations)
		 * @param value Valeur à écrire à l'adresse renseignée.
		 */
		void write(unsigned short address, unsigned char value);
		/*!
		 * @brief La fonction read permet de lire des données dans un des quatres channels de l'APU.
		 * @param address Adresse où la fonction read lit. (Les valeurs sont légèrement modifiés de l'original, voir l'enumération regist pour plus d'informations)
		 * @return La valeur écrite à l'adresse renseignée dans la fonction.
		 */
		unsigned char read(unsigned short address) const;
		/*!
		 * @brief La fonction update permet d'effectuer des mises à jours des sons joués.
		 * Il est souvent utilisé lorsqu'un son joué est soumis à un blayage/changement continu de volume ou de fréquence.
		 * @param cycleNB La nombre de cycles écoulés depuis le début du CPU
		 */
		void update(unsigned cycleNB); // retourne le nombre de cycle écoulés depuis le début du CPU

		//RegisterFunctions
		/*!
		 * @brief Permet de lire dans le channel 1 spécifiquement.
		 * @param address Adresse de lecture dans le channel 1.
		 * @return La valeur écrite à l'adresse renseignée.
		 */
		unsigned char channelOneReading(unsigned short address) const;
		/*!
		 * @brief Permet de lire dans le channel 2 spécifiquement.
		 * @param address Adresse de lecture dans le channel 2.
		 * @return La valeur écrite à l'adresse renseignée.
		 */
		unsigned char channelTwoReading(unsigned short address) const;
		/*!
		 * @brief Permet de lire dans le channel wave spécifiquement.
		 * @param address Adresse de lecture dans le channel wave.
		 * @return La valeur écrite à l'adresse renseignée.
		 */
		unsigned char channelWaveReading(unsigned short address) const;
		/*!
		 * @brief Permet de lire dans le channel noise spécifiquement.
		 * @param address Adresse de lecture dans le channel noise.
		 * @return La valeur écrite à l'adresse renseignée.
		 */
		unsigned char channelNoiseReading(unsigned short address) const;
		/*!
		 * @brief Permet de lire dans les contrôles de sons généraux.
		 * @param address Adresse de lecture dans les contrôles de sons généraux.
		 * @return La valeur écrite à l'adresse renseignée.
		 */
		unsigned char controllerReading(unsigned short address) const;

		/*!
		 * @brief Permet d'écrire dans le channel 1 spécifiquement.
		 * @param address Adresse d'écriture dans le channel 1.
		 * @param value Valeur écrite dans le channel 1.
		 */
		void channelOneWriting(unsigned short address, unsigned char value);
		/*!
		 * @brief Permet d'écrire dans le channel 2 spécifiquement.
		 * @param address Adresse d'écriture dans le channel 2.
		 * @param value Valeur écrite dans le channel 2.
		 */
		void channelTwoWriting(unsigned short address, unsigned char value);
		/*!
		 * @brief Permet d'écrire dans le channel wave spécifiquement.
		 * @param address Adresse d'écriture dans le channel wave.
		 * @param value Valeur écrite dans le channel wave.
		 */
		void channelWaveWriting(unsigned short address, unsigned char value);
		/*!
		 * @brief Permet d'écrire dans le channel noise spécifiquement.
		 * @param address Adresse d'écriture dans le channel noise.
		 * @param value Valeur écrite dans le channel noise.
		 */
		void channelNoiseWriting(unsigned short address, unsigned char value);
		/*!
		 * @brief Permet d'écrire dans les contrôles de sons généraux.
		 * @param address Adresse d'écriture dans les contrôles de sons généraux.
		 * @param value Valeur écrite dans les contrôles de sons généraux.
		 */
		void controllerWriting(unsigned short address, unsigned char value);

		/*!
		 * @brief Permet d'écrire et de changer la valeur dans le Vin.
		 * @param value Nouvelle valeur du Vin
		 */
		void setVin(unsigned char value);
		/*!
		 * @brief Permet de lire la valeur du Vin.
		 * @return Valeur du Vin
		 */
		unsigned char getVin() const;
		/*!
		 * @brief Permet d'écrire et de changer la valeur des sorties sons.
		 * Actuellement, le son d'un channel est redirigé dans un terminal de sortie.
		 * Ici est la gestion de quel channel est redirigé vers quel sortie son. (SO1 ou SO2)
		 * @param value Nouvelle valeur du SOTS
		 */
		void setSOTS(unsigned char value); // setting SoundOutputTerminalSelection;
		/*!
		 * @brief Permet de lire la valeur des sorties sons.
		 * @return Valeur du SOTS
		 */
		unsigned char getSOTS() const; // getting it
		/*!
		 * @brief Permet d'écrire la nouvelle valeur du registre SoundOnOff.
		 * @param value Nouvelle valeur du registre
		 */
		void setSoundOnOff(unsigned char value);
		/*!
		 * @brief Permet de lire la valeur écrite dans le registre SoundOnOff.
		 * @return Nouvelle valeur du registre
		 */
		unsigned char getSoundOnOff() const;

	private:
		/*!
		 * @brief Channel 1
		 */
		SoundChannel::SquareWaveChannel _managerChannel1;

		/*!
		 * @brief Channel 2
		 */
		SoundChannel::SquareWaveChannel _managerChannel2;

		/*!
		 * @brief Channel Wave
		 */
		SoundChannel::ModulableWaveChannel _managerChannelWave; //wave output

		/*!
		 * @brief Channel Noise
		 */
		SoundChannel::NoiseChannel _managerChannelNoise;//noise channel

		//ChannelControl / ON/OFF / Volume
		/*!
		 * @brief Sortir le vin par le SO2
		 */
		 bool _VinToSo2 = false;
		/*!
		 * @brief Master Volume for SO2
		 */
		unsigned char _SO2OutputLevel = 0;
		/*!
		 * @brief Sortir le vin par le SO1
		 */
		bool _VinToSo1 = false;
		/*!
		 * @brief Master Volume for SO1
		 */
		unsigned char _SO1OutputLevel = 0;

		//Sound Output Terminal Selection
		/*!
		 * @brief Valeur du SOTS
		 */
		unsigned char _soundOutputTerminalSelection = 0;

		//Sound ON/OFF Flags and Power Button
		/*!
		 * @brief Valeur du "bouton On/Off" général de l'APU
		 */
		bool _allSoundsOn = false;
		/*!
		 * @brief Flag de lecture _soundOnOff1 : Si le channel 1 est On ou Off
		 */
		bool _soundOnOff1 = false;
		/*!
		 * @brief Flag de lecture _soundOnOff2 : Si le channel 2 est On ou Off
		 */
		bool _soundOnOff2 = false;
		/*!
		 * @brief Flag de lecture _soundOnOffWave : Si le channel Wave est On ou Off
		 */
		bool _soundOnOffWave = false;
		/*!
		 * @brief Flag de lecture _soundOnOffNoise : Si le channel Noise est On ou Off
		 */
		bool _soundOnOffSound = false;
		//Memory::Memory _memory;
	};
}


#endif //GBEMULATOR_APU_HPP
