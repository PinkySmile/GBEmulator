/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.cpp
*/

#include "APU.hpp"

namespace GBEmulator
{
    APU::APU(ISound &channelOne, ISound &channelTwo, ISound &channelThree, ISound &channelFour) :
    _soundChannel1(channelOne),
    _soundChannel2(channelTwo),
    _soundChannelWave(channelThree),
    _soundChannelNoise(channelFour),
    _soundControllers(SOUND_CONTROLERS_SIZE, SOUND_CONTROLERS_SIZE),
    _wpRAM(CHANSIZE_WPRAM, CHANSIZE_WPRAM)
    {

    }

    APU::~APU() = default;

    void APU::write(unsigned short address, unsigned char value)
    {
        this->_soundChanged = true;
        switch (address) {
            case FF10 ... FF14 :
                //this->_soundMode1.write(address - FF10, value);
                break;
            case FF16 ... FF19 :
                //this->_soundMode2.write(address - FF16, value);
                break;
            case FF1A ... FF1E :
                //this->_soundWave.write(address - FF1A, value);
                break;
            case FF20 ... FF24 :
                //this->_soundNoise.write(address - FF20, value);
                break;
            case FF25 ... FF26 :
                this->_soundControllers.write(address - FF25, value);
                this->_soundChanged = false;
                break;
            case FF30 ... FF3F :
                this->_wpRAM.write(address - FF30, value);
                break;
            default :
                this->_soundChanged = false;
                break;
        }
    }

    unsigned char APU::soundModeOneCorrectRead(unsigned short address) const
    {
        switch (address) {
            case FF10 :
                return this->_soundMode1.read(address - FF10);
            case FF11 :
                return this->_soundMode1.read(address - FF10) | 0b00111111;
            case FF12 :
                return this->_soundMode1.read(address - FF10);
            case FF13 :
                return 0xFF;
            case FF14 :
                return this->_soundMode1.read(address - FF10) | 0b10111111;
            default :
                return 0xFF;

        }
    }

    unsigned char APU::soundModeTwoCorrectRead(unsigned short address) const
    {
        switch (address) {
            case FF16 :
                return this->_soundMode2.read(address - FF16) | 0b00111111;
            case FF17 :
                return this->_soundMode2.read(address - FF16);
            case FF18 :
                return 0xFF;
            case FF19 :
                return this->_soundMode2.read(address - FF16) | 0b10111111;
            default :
                return 0xFF;

        }
    }

    unsigned char APU::soundWaveCorrectRead(unsigned short address) const
    {
        switch (address) {
            case FF1A :
                return this->_soundWave.read(address - FF1A) | 0b01111111;
            case FF1B :
                return this->_soundWave.read(address - FF1A);
            case FF1C :
                return this->_soundWave.read(address - FF1A) | 0b10011111;
            case FF1D :
                return 0xFF;
            case FF1E :
                return this->_soundWave.read(address - FF1A) | 0b10111111;
            default :
                return 0xFF;
        }
    }

    unsigned char APU::soundNoiseCorrectRead(unsigned short address) const
    {
        switch (address) {
            case FF20 :
                return this->_soundNoise.read(address - FF20) | 0b00011111;
            case FF21 :
                return this->_soundNoise.read(address - FF20);
            case FF22 :
                return this->_soundNoise.read(address - FF20);
            case FF23 :
                return this->_soundNoise.read(address - FF20) | 0b10111111;
            case FF24 :
                return this->_soundNoise.read(address - FF20);
            default :
                return 0xFF;
        }
    }

    unsigned char APU::soundControlersCorrectRead(unsigned short address) const
    {
        switch (address) {
            case FF25 :
                return this->_soundNoise.read(address - FF25) | 0b00000000;
            case FF26 :
                return this->_soundNoise.read(address - FF25) | 0b01110000;
            default :
                return 0xFF;
        }
    }

    unsigned char APU::read(unsigned short address) const
    {
        switch (address) {
            case FF10 ... FF14 :
                return soundModeOneCorrectRead(address);
            case FF16 ... FF19 :
                return soundModeTwoCorrectRead(address);
            case FF1A ... FF1E :
                return soundWaveCorrectRead(address);
            case FF20 ... FF24 :
                return soundNoiseCorrectRead(address);
            case FF25 ... FF26 :
                return soundControlersCorrectRead(address);
            case FF30 ... FF3F :
                return this->_wpRAM.read(address);
            default :
                return 0xFF;

        }
    }

    void APU::update(unsigned cycleNB)
    {
        if (read(FF26) >> 7) {
            //soundModeOne
            //soundModeTwo
            //soundModeThree
            //soundModeFour
        } else {
            //StopAllSounds
        }
    }
}