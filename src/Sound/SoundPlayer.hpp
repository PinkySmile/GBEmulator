/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SoundPlayer.hpp
*/


#ifndef GBEMULATOR_SOUNDPLAYER_HPP
#define GBEMULATOR_SOUNDPLAYER_HPP

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "ISound.hpp"

namespace GBEmulator {
	/*!
	 * @brief SoundPlayer implémente les fonctions de l'interface ISound.
	 * La classe contient les fonctions qui permettent de modifier le volume, la fréquence et l'exécution du son.
	 */
	class SoundPlayer : public ISound
	{
	public:
		/*!
		 * @brief Constructeur de la classe SoundPlayer.
		 * Lance la lecture d'un son sur deux sorties différentes (SO1 et SO2) en volume 0.
		 */
		SoundPlayer();
		~SoundPlayer() override = default;

		void setDisabled(bool disabled) override;
		void setPitch(float frequency) override;
		void setWave(std::vector<unsigned char> samples, unsigned int sampleRate) override;
		void setVolume(float volume) override;
		void setSO1Volume(float volume) override;
		void setSO2Volume(float volume) override;

	private:
		/*!
		 * @brief True -> Arrêt de la lecture du son / False -> Reprise de la lecture du son
		 */
		bool _disabled = false;
		/*!
		 * @brief Son du SO1 (channel de gauche)
		 */
		sf::Sound _soundSO1;
		/*!
		 * @brief Son du SO2 (channel de droite)
		 */
		sf::Sound _soundSO2;
		/*!
		 * @brief Buffer qui contient la wave du son joué
		 */
		sf::SoundBuffer _soundBuffer;
		/*!
		 * @brief Volume général
		 */
		float _volume = 0;
		/*!
		 * @brief Volume général du son joué à gauche
		 */
		float _volumeSO1 = 100;
		/*!
		 * @brief Volume général du son joué à droite
		 */
		float _volumeSO2 = 100;
	};
}


#endif //GBEMULATOR_SOUNDPLAYER_HPP
