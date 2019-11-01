/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** SoundPlayer.cpp
*/

#include "SoundPlayer.hpp"

namespace GBEmulator {

    GBEmulator::SoundPlayer::SoundPlayer() :
    _sound()
    {
        this->_sound.play();
    }

    void GBEmulator::SoundPlayer::setFrequency(float frequency)
    {
        this->_sound.setPitch(131072 / (2048 - frequency));
    }

    void GBEmulator::SoundPlayer::setWave(std::vector<unsigned char> wave)
    {
        if (wave.size() == 1) {
            switch (wave[0]) {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
        }
    }

    void GBEmulator::SoundPlayer::setVolume(float volume)
    {
        this->_sound.setVolume(100 / 16 * volume);
    }

}
