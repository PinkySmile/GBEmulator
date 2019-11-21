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

		void setPitch(float frequency) override;
		void setWave(std::vector<unsigned char> samples, unsigned int sampleRate) override;
		void setVolume(float volume) override;
	private:
		bool _loop = false;
		sf::Sound _sound;
		sf::SoundBuffer _soundBuffer;
		float _volume = 0;
	};
}


#endif //GBEMULATOR_SOUNDPLAYER_HPP
