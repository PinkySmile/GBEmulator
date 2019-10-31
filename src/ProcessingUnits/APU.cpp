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
    _managerChannel1(channelOne),
    _managerChannel2(channelTwo),
    _managerChannelWave(channelThree),
    _managerChannelNoise(channelFour),
    _controller(),
    _wpRAM(CHANSIZE_WPRAM, CHANSIZE_WPRAM)
    {

    }

    APU::~APU() = default;

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

    void APU::write(unsigned short address, unsigned char value)
    {
        this->_soundChanged = true;
        switch (address) {
            case FF10 ... FF14 :
                channelOneWriting(address, value);
                break;
            case FF16 ... FF19 :
                channelTwoWriting(address - FF16, value);
                break;
            case FF1A ... FF1E :
                channelWaveWriting(address - FF1A, value);
                break;
            case FF20 ... FF23 :
                channelNoiseWriting(address - FF20, value);
                break;
            case FF24 ... FF26 :
                controllerWriting(address - FF24, value);
                this->_soundChanged = false;
                break;
            case WPRAM_START ... WPRAM_END :
                this->_wpRAM.write(address - WPRAM_START, value);
                break;
            default :
                this->_soundChanged = false;
                break;
        }
    }

    unsigned char APU::read(unsigned short address) const
    {
        switch (address) {
            case FF10 ... FF14 :
                return channelOneReading(address - FF10);
            case FF16 ... FF19 :
                return channelTwoReading(address - FF16);
            case FF1A ... FF1E :
                return channelWaveReading(address - FF1A);
            case FF20 ... FF23 :
                return channelNoiseReading(address - FF20);
            case FF24 ... FF26 :
                return controllerReading(address - FF24);
            case WPRAM_START ... WPRAM_END :
                return this->_wpRAM.read(address);
            default :
                return 0xFF;

        }
    }

    //
    //ChannelOneReading and Writing
    //

    unsigned char APU::channelOneReading(unsigned short address) const
    {
        switch (address) {
            case 0x0 :
                return this->_managerChannel1.getSweep();
            case 0x1 :
                return this->_managerChannel1.getWave();
            case 0x2 :
                return this->_managerChannel1.getVolume();
            case 0x3 :
                return 0xFF;
            case 0x4 :
                return this->_managerChannel1.getRestartOptions();
            default :
                return 0xFF;

        }
    }

    void APU::channelOneWriting(unsigned short address, unsigned char value)
    {
        switch (address) {
            case 0x0 :
                this->_managerChannel1.setSweep(value);
            case 0x1 :
                this->_managerChannel1.setWave(value);
            case 0x2 :
                this->_managerChannel1.setVolume(value);
            case 0x3 :
                this->_managerChannel1.setHighFrequency(value);
            case 0x4 :
                this->_managerChannel1.setRestartOptions(value);
            default :
                0xFF;

        }
    }

    //
    //ChannelTwo Reading and Writing
    //

    unsigned char APU::channelTwoReading(unsigned short address) const
    {
        switch (address) {
            case 0x0 :
                return this->_managerChannel2.getWave();
            case 0x1 :
                return this->_managerChannel2.getVolume();
            case 0x2 :
                return 0xFF;
            case 0x3 :
                return this->_managerChannel2.getRestartOptions();
            default :
                return 0xFF;

        }
    }

    void APU::channelTwoWriting(unsigned short address, unsigned char value)
    {
        switch (address) {
            case 0x0 :
                this->_managerChannel2.setWave(value);
            case 0x1 :
                this->_managerChannel2.setVolume(value);
            case 0x2 :
                0xFF;
            case 0x3 :
                this->_managerChannel2.setRestartOptions(value);
            default :
                0xFF;

        }
    }

    //
    //ChannelWave Reading and Writing
    //

    unsigned char APU::channelWaveReading(unsigned short address) const
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

    void APU::channelWaveWriting(unsigned short address, unsigned char value)
    {
        switch (address) {
            case FF1A :
                this->_soundWave.read(address - FF1A) | 0b01111111;
            case FF1B :
                this->_soundWave.read(address - FF1A);
            case FF1C :
                this->_soundWave.read(address - FF1A) | 0b10011111;
            case FF1D :
                0xFF;
            case FF1E :
                this->_soundWave.read(address - FF1A) | 0b10111111;
            default :
                0xFF;
        }
    }


    //
    // channel Noise Reading and Writing
    //

    unsigned char APU::channelNoiseReading(unsigned short address) const
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
            default :
                return 0xFF;
        }
    }

    void APU::channelNoiseWriting(unsigned short address, unsigned char value)
    {
        switch (address) {
            case FF20 :
                this->_soundNoise.read(address - FF20) | 0b00011111;
            case FF21 :
                this->_soundNoise.read(address - FF20);
            case FF22 :
                this->_soundNoise.read(address - FF20);
            case FF23 :
                this->_soundNoise.read(address - FF20) | 0b10111111;
            default :
                0xFF;
        }
    }

    //
    // General getter/Setters from SOUND
    //

    void APU::Sound::setSweep(unsigned char value)
    {
        this->_sweepTime = (value & 0b01110000) >> 4;
        this->_sweepDirection = (value & 0b00001000) >> 3;
        this->_sweepShiftNumber = (value & 0b00000111);
    }

    unsigned char APU::Sound::getSweep() const
    {
        unsigned char value = 0b00000001;

        value <<= 3;
        value |= this->_sweepTime;
        value <<= 1;
        value |= this->_sweepDirection;
        value <<= 3;
        return (value | this->_sweepShiftNumber);
    }

    void APU::Sound::setWave(unsigned char value)
    {
        this->_wavePattern = value >> 6;
        this->_soundLength = value & 0b00111111;
    }

    unsigned char APU::Sound::getWave() const
    {
        unsigned char value = this->_wavePattern;

        value <<= 6;
        return (value | 0b00111111);
    }

    void APU::Sound::setVolume(unsigned char value)
    {
        this->_initialVolume = value >> 4;
        this->_volumeDirection = (value & 0b00001000) >> 3;
        this->_volumeShiftNumber = value & 0b00000111;
    }

    unsigned char APU::Sound::getVolume() const
    {
        unsigned char value = this->_initialVolume;

        value <<= 1;
        value |= this->_volumeDirection;
        value <<= 3;
        return (value | this->_volumeShiftNumber);
    }

    void APU::Sound::setHighFrequency(unsigned char value)
    {
        this->_highFrequency = value;
    }

    void APU::Sound::setRestartOptions(unsigned char value)
    {
        this->_restart = value >> 7;
        this->_restartType = (value & 0b01000000) >> 6;
        this->_lowFrenquency = value & 0b00000111;
    }

    unsigned char APU::Sound::getRestartOptions() const
    {
        unsigned char value = this->_restart;

        value <<= 1;
        value |= this->_restartType;
        value <<= 3;
        value |= 0b00000111;
        value <<= 3;
        return (value | this->_lowFrenquency);
    }

    //
    //Controller Implementation
    //

    unsigned char APU::controllerReading(unsigned short address) const
    {
        switch (address) {
            case 0x0 :
                return this->_controller.getVin();
            case 0x1 :
                return this->_controller.getSOTS();
            case 0x2 :
                return this->_controller.getSoundOnOff();
            default :
                return 0xFF;
        }
    }

    void APU::controllerWriting(unsigned short address, unsigned char value)
    {
        switch (address) {
            case 0x0:
                this->_controller.setVin(value);
                break;
            case 0x1:
                this->_controller.setSOTS(value);
                break;
            case 0x2:
                this->_controller.setSoundOnOff(value);
                break;
            default:
                return;
        }
    }

    void APU::Controller::setVin(unsigned char value)
    {
        this->_VinToSo2 = value >> 7;
        this->_SO2OutputLevel = (value & 0b01110000) >> 4;
        this->_VinToSo1 = (value & 0b00001000) >> 3;
        this->_SO1OutputLevel = (value & 0b00000111);
    }

    unsigned char APU::Controller::getVin() const
    {
        unsigned char value = this->_VinToSo2;

        value <<= 3;
        value |= this->_SO2OutputLevel;
        value <<= 1;
        value |= this->_VinToSo1;
        value <<= 3;
        return (value | this->_SO1OutputLevel);
    }

    void APU::Controller::setSOTS(unsigned char value)
    {
        this->_soundOutputTerminalSelection = value;
    }

    unsigned char APU::Controller::getSOTS() const
    {
        return (this->_soundOutputTerminalSelection);
    }

    void APU::Controller::setSoundOnOff(unsigned char value)
    {
        this->_allSoundsOn = value >> 7;
    }

    unsigned char APU::Controller::getSoundOnOff() const
    {
        unsigned char value = this->_allSoundsOn;

        value <<= 3;
        value |= 0b00000111;
        value <<= 1;
        value |= this->_soundOnOff1;
        value <<= 1;
        value |= this->_soundOnOff2;
        value <<= 1;
        value |= this->_soundOnOffWave;
        value <<= 1;
        return (value | this->_soundOnOffSound);
    }
}