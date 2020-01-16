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
	class SoundPlayer : public ISound
	{
	public:
		SoundPlayer();
		~SoundPlayer() = default;
		SoundPlayer(const SoundPlayer &) = delete;
		SoundPlayer &operator=(const SoundPlayer &) = delete;

		void setDisabled(bool disabled) override;
		void setPitch(float frequency) override;
		void setWave(std::vector<unsigned char> samples, unsigned int sampleRate) override;
		void setVolume(float volume) override;
		void setSO1Volume(float volume) override;
		void setSO2Volume(float volume) override;

	private:
		bool _disabled = false;
		sf::Sound _soundSO1;
		sf::Sound _soundSO2;
		sf::SoundBuffer _soundBuffer;
		float _volume = 0;
		float _volumeSO1 = 100;
		float _volumeSO2 = 100;
	};
}


#endif //GBEMULATOR_SOUNDPLAYER_HPP
