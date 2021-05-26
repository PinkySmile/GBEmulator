/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.hpp
*/

#ifndef GBEMULATOR_APU_HPP
#define GBEMULATOR_APU_HPP

#define DIV_FREQUENCY 4194304

#ifndef ARDUINO
#include <memory>
#include <cstdint>
#else
#include <stdint.h>
#include "../ArduinoStuff/Memory.hpp"
#endif
#include "../Memory/Memory.hpp"
#include "../Sound/ISound.hpp"
#include "SoundChannel/IGBSoundChannel.hpp"

namespace GBEmulator
{
	/*!
	 * @brief Liste des adresses que le CPU peut envoyer à l'APU.
	 * Acutellement, n'utilise qu'une partie des adresses.
	 */
	enum APURegisters {
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
		NR10 = FF10,
		NR11,
		NR12,
		NR13,
		NR14,
		NR20,
		NR21,
		NR22,
		NR23,
		NR24,
		NR30,
		NR31,
		NR32,
		NR33,
		NR34,
		NR40,
		NR41,
		NR42,
		NR43,
		NR44,
		NR50,
		NR51,
		NR52,
		WPRAM_START = 0x20,
		WPRAM_END = 0x2F
	};

	enum APUInternalRegisters {
		APU_CHANNEL_CONTROL,
		APU_SOT_SELECTION,
		APU_SOUND_ON_OFF
	};

	class SampleBuffer {
	public:
		standard::vector<int16_t> _buffer;
		float leftVolume = 1;
		float rightVolume = 1;

		SampleBuffer &operator=(const standard::vector<int16_t> &samples);
		SampleBuffer &operator<<(const standard::vector<int16_t> &samples);
		SampleBuffer &operator+=(const standard::vector<int16_t> &samples);
	};

	struct APUSoundOutputTerminalSelect {
		bool outputSound1toSO1 : 1;
		bool outputSound2toSO1 : 1;
		bool outputSound3toSO1 : 1;
		bool outputSound4toSO1 : 1;
		bool outputSound1toSO2 : 1;
		bool outputSound2toSO2 : 1;
		bool outputSound3toSO2 : 1;
		bool outputSound4toSO2 : 1;

		APUSoundOutputTerminalSelect(unsigned char v) { *this = v; };
		APUSoundOutputTerminalSelect &operator=(unsigned char v) { *reinterpret_cast<unsigned char *>(this) = v; return *this; }
		operator unsigned char() const { return *reinterpret_cast<const unsigned char *>(this); }
	};

	struct APUChannelControl {
		unsigned char SO1volume : 3;
		bool vinToSO1 : 1;
		unsigned char SO2volume : 3;
		bool vinToSO2 : 1;

		APUChannelControl(unsigned char v) { *this = v; };
		APUChannelControl &operator=(unsigned char v) { *reinterpret_cast<unsigned char *>(this) = v; return *this; }
		operator unsigned char() const { return *reinterpret_cast<const unsigned char *>(this); }
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
		 * @param soundPlayer Interface ISound permettant de jouer le son produit.
		 */
		APU(ISound &soundPlayer);

		/*!
		 * @brief La fonction write permet d'écrire des données dans un des quatres channels de l'APU.
		 * @param address Adresse d'écriture dans le channel. (Les valeurs sont légèrement modifiés de l'original, voir l'enumération regist pour plus d'informations)
		 * @param value Valeur à écrire à l'adresse renseignée.
		 */
		void write(uint16_t address, uint8_t value);
		/*!
		 * @brief La fonction read permet de lire des données dans un des quatres channels de l'APU.
		 * @param address Adresse où la fonction read lit. (Les valeurs sont légèrement modifiés de l'original, voir l'enumération regist pour plus d'informations)
		 * @return La valeur écrite à l'adresse renseignée dans la fonction.
		 */
		unsigned char read(uint16_t address) const;
		/*!
		 * @brief La fonction update permet d'effectuer des mises à jours des sons joués.
		 * Il est souvent utilisé lorsqu'un son joué est soumis à un blayage/changement continu de volume ou de fréquence.
		 * @param cycleNB La nombre de cycles écoulés depuis le début du CPU
		 */
		void update(unsigned cycleNB); // retourne le nombre de cycle écoulés depuis le début du CPU

	private:
		void _internalWrite(unsigned short relativeAddress, uint8_t value);
		unsigned char _internalRead(unsigned short relativeAddress) const;
		standard::vector<int16_t> _updateAndProcessChannelSound(int channelNb, unsigned cycles);

		//! @brief Lecteur de son
		ISound &_soundPlayer;

		//! @brief Sample buffer
		SampleBuffer _samples;

		//! @brief Tous les channels
		standard::unique_ptr<IGBSoundChannel> _channels[4];

		bool _enabled = false;
		APUSoundOutputTerminalSelect _terminalSelect = 0x00;
		APUChannelControl _channelControl = 0x00;
	};
}


#endif //GBEMULATOR_APU_HPP
