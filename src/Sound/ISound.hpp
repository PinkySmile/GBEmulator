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
        virtual void setDisabled(bool disabled) = 0;
        virtual void setPitch(float frequency) = 0;
        virtual void setWave(std::vector<unsigned char> samples, unsigned int sampleRate) = 0;
        virtual void setVolume(float volume) = 0;
        virtual void setSO1(bool activated) = 0;
        virtual void setSO2(bool activated) = 0;
    };
}


#endif //GBEMULATOR_ISOUND_HPP
