/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SoundPlayer.hpp
*/


#ifndef GBEMULATOR_SFMLSOUNDPLAYER_HPP
#define GBEMULATOR_SFMLSOUNDPLAYER_HPP


#include <SFML/Audio.hpp>
#include "ISound.hpp"

#define NB_SAMPLE_BUFFER 1

namespace GBEmulator {
	/*!
	 * @brief SFMLSoundPlayer implémente les fonctions de l'interface ISound avec la SFML audio.
	 * La classe contient les fonctions qui permettent de modifier le volume, la fréquence et l'exécution du son.
	 */
	class SFMLSoundPlayer : public ISound, public sf::SoundStream
	{
	public:
		/*!
		 * @brief Constructeur de la classe SoundPlayer.
		 * Lance la lecture d'un son sur deux sorties différentes (SO1 et SO2) en volume 0.
		 */
		SFMLSoundPlayer();
		~SFMLSoundPlayer() override;

		void setVolume(float volume) override;
		void pushSamples(int16_t *samples, size_t sampleCount) override;

	private:
		virtual bool onGetData(Chunk &data);
		virtual void onSeek(sf::Time timeOffset);
		/*!
		 * @brief Volume général
		 */
		float _masterVolume = 0;
		bool mutex = false;
		int8_t readHead = 0;
		int8_t writeHead = 0;
		std::vector<int16_t> _samples[NB_SAMPLE_BUFFER];
		std::vector<int16_t> _buffer;
	};
}


#endif //GBEMULATOR_SFMLSOUNDPLAYER_HPP
