//
// Created by jmartin on 10/24/19.
//

#ifndef GBEMULATOR_ISOUND_HPP
#define GBEMULATOR_ISOUND_HPP

#include <vector>

namespace GBEmulator {
    class ISound {
        virtual void play(float frequency) = 0;
        virtual void stop() = 0;
        virtual void setWave(std::vector<unsigned char>) = 0;
        virtual void setVolume(float volume) = 0;
    };
}


#endif //GBEMULATOR_ISOUND_HPP
