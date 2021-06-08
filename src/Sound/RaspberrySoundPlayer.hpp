//
// Created by andgel on 03/06/2021
//

#ifndef GBEMULATOR_RASPBERRYSOUNDPLAYER_HPP
#define GBEMULATOR_RASPBERRYSOUNDPLAYER_HPP


#include <thread>
#include "ISound.hpp"

namespace GBEmulator {
	/*!
	 * @brief SFMLSoundPlayer implémente les fonctions de l'interface ISound avec la SFML audio.
	 * La classe contient les fonctions qui permettent de modifier le volume, la fréquence et l'exécution du son.
	 */
	class RaspberrySoundPlayer : public ISound
	{
	public:
		/*!
		 * @brief Constructeur de la classe SoundPlayer.
		 * Lance la lecture d'un son sur deux sorties différentes (SO1 et SO2) en volume 0.
		 */
		RaspberrySoundPlayer();
		~RaspberrySoundPlayer() override;

		void setVolume(float volume) override;
		void pushSamples(int16_t *samples, size_t sampleCount) override;

	private:
		/*!
		 * @brief Volume général
		 */
		 std::thread _thread;
		float _masterVolume = 0;
		unsigned _head;
		std::vector<int16_t> _buffer;
	};
}


#endif //GBEMULATOR_RASPBERRYSOUNDPLAYER_HPP
