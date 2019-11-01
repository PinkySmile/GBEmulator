/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ISound.hpp
*/


#ifndef GBEMULATOR_ISOUND_HPP
#define GBEMULATOR_ISOUND_HPP

#include <vector>

namespace GBEmulator {
    class ISound {
    public:
        virtual void setFrequency(float frequency) = 0;
        virtual void setWave(std::vector<unsigned char>) = 0;
        virtual void setVolume(float volume) = 0;
    };
}


#endif //GBEMULATOR_ISOUND_HPP
