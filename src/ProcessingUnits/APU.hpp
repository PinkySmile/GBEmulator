/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.hpp
*/

#ifndef GBEMULATOR_APU_HPP
#define GBEMULATOR_APU_HPP

#define DIV_FREQUENCY 4194304

#include "../Memory/Memory.hpp"
#include "../Sound/ISound.hpp"
#include "SoundChannel/SoundChannel.hpp"
#include "SoundChannel/SquareWaveChannel.hpp"
#include "SoundChannel/NoiseChannel.hpp"
#include "SoundChannel/ModulableWaveChannel.hpp"

namespace GBEmulator
{
	enum regist {
		FF10 = 0x0,
		FF11 = 0x1,
		FF12 = 0x2,
		FF13 = 0x3,
		FF14 = 0x4,
		FF16 = 0x6,
		FF17 = 0x7,
		FF18 = 0x8,
		FF19 = 0x9,
		FF1A = 0xA,
		FF1B = 0xB,
		FF1C = 0xC,
		FF1D = 0xD,
		FF1E = 0xE,
		FF20 = 0x10,
		FF21 = 0x11,
		FF22 = 0x12,
		FF23 = 0x13,
		FF24 = 0x14,
		FF25 = 0x15,
		FF26 = 0x16,
		WPRAM_START = 0x20,
		WPRAM_END = 0x2F
	};

	class APU {
	public:
		APU() = delete;
		APU(ISound &channelOne, ISound &channelTwo, ISound &channelThree, ISound &channelFour);
		~APU() = default;
		APU(const APU &) = delete;
		APU &operator=(const APU &) = delete;

		void write(unsigned short, unsigned char);
		unsigned char read(unsigned short) const;
		void update(unsigned cycleNB); // retourne le nombre de cycle écoulés depuis le début du CPU
		//cycle(); // effectue un cycle

		//RegisterFunctions
		unsigned char channelOneReading(unsigned short) const;
		unsigned char channelTwoReading(unsigned short) const;
		unsigned char channelWaveReading(unsigned short) const;
		unsigned char channelNoiseReading(unsigned short) const;
		unsigned char controllerReading(unsigned short) const;

		void channelOneWriting(unsigned short, unsigned char);
		void channelTwoWriting(unsigned short, unsigned char);
		void channelWaveWriting(unsigned short, unsigned char);
		void channelNoiseWriting(unsigned short, unsigned char);
		void controllerWriting(unsigned short, unsigned char);

		void setVin(unsigned char value);
		unsigned char getVin() const;
		void setSOTS(unsigned char value); // setting SoundOutputTerminalSelection;
		unsigned char getSOTS() const; // getting it
		void setSoundOnOff(unsigned char value);
		unsigned char getSoundOnOff() const;

	private:
		//soundChannel1
		SoundChannel::SquareWaveChannel _managerChannel1;

		//soundChannel2
		SoundChannel::SquareWaveChannel _managerChannel2;

		//soundChannelWave
		SoundChannel::ModulableWaveChannel _managerChannelWave; //wave output

		//soundChannelNoise
		SoundChannel::NoiseChannel _managerChannelNoise;//noise channel

		//ChannelControl / ON/OFF / Volume
		bool _VinToSo2 = false;
		unsigned char _SO2OutputLevel = 0;
		bool _VinToSo1 = false;
		unsigned char _SO1OutputLevel = 0;

		//Sound Output Terminal Selection
		unsigned char _soundOutputTerminalSelection = 0;

		//Sound ON/OFF Flags and Power Button
		bool _allSoundsOn = false;
		bool _soundOnOff1 = false;
		bool _soundOnOff2 = false;
		bool _soundOnOffWave = false;
		bool _soundOnOffSound = false;
		//Memory::Memory _memory;
	};
}


#endif //GBEMULATOR_APU_HPP
