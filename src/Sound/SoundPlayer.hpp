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

        void setFrequency(float frequency) override;
        void setWave(std::vector<unsigned char>) override;
        void setVolume(float volume) override;
    private:
        sf::Sound _sound;
        sf::SoundBuffer _soundBuffer;
        float _frequency = 0;
        float _volume = 0;

    };
}


#endif //GBEMULATOR_SOUNDPLAYER_HPP