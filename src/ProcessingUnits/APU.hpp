/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.hpp
*/

#ifndef GBEMULATOR_APU_HPP
#define GBEMULATOR_APU_HPP

#define DIV_FREQUENCY 4194304

#include <memory>
#include "../Memory/Memory.hpp"
#include "../Sound/ISound.hpp"
#include "SoundChannel/IGBSoundChannel.hpp"

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
		NR10 = FF10,
		NR11 = FF11,
		NR12 = FF12,
		NR13 = FF13,
		NR14 = FF14,
		NR21 = FF16,
		NR22 = FF17,
		NR23 = FF18,
		NR24 = FF19,
		NR30 = FF1A,
		NR31 = FF1B,
		NR32 = FF1C,
		NR33 = FF1D,
		NR34 = FF1E,
		NR41 = FF20,
		NR42 = FF21,
		NR43 = FF22,
		NR44 = FF23,
		NR50 = FF24,
		NR51 = FF25,
		NR52 = FF26,
		WPRAM_START = 0x20,
		WPRAM_END = 0x2F
	};

	class SampleBuffer {
	public:
		std::vector<short> _buffer;

		SampleBuffer &operator=(const std::vector<short> &samples);
		SampleBuffer &operator<<(const std::vector<short> &samples);
		SampleBuffer &operator+=(const std::vector<short> &samples);
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

	private:
		//! @brief Lecteur de son
		ISound &_soundPlayer;

		SampleBuffer _samples;

		//! @brief Tous les channels
		std::unique_ptr<IGBSoundChannel> _channels[4];
	};
}


#endif //GBEMULATOR_APU_HPP
