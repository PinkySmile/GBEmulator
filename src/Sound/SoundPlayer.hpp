/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SoundPlayer.hpp
*/


#ifndef GBEMULATOR_SOUNDPLAYER_HPP
#define GBEMULATOR_SOUNDPLAYER_HPP

#include "ISound.hpp"

namespace GBEmulator {
    class SoundPlayer : public ISound
    {
    public:
        SoundPlayer() = default;
        ~SoundPlayer() = default;
        SoundPlayer(const SoundPlayer &) = delete;
        SoundPlayer &operator=(const SoundPlayer &) = delete;

        void setFrequency(float frequency) override;
        void setWave(std::vector<unsigned char>) override;
        void setVolume(float volume) override;
    private:
        float _frequency = 0;
        float _volume = 0;

    };
}


#endif //GBEMULATOR_SOUNDPLAYER_HPP
