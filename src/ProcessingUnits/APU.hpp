/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.hpp
*/

#ifndef GBEMULATOR_APU_HPP
#define GBEMULATOR_APU_HPP

#define CHANSIZE_1 0x5
#define CHANSIZE_2 0x4
#define CHANSIZE_WAVE 0x5
#define CHANSIZE_NOISE 0x5
#define SOUND_CONTROLERS_SIZE 0x2
#define CHANSIZE_WPRAM 0xF

#include "../Memory/Memory.hpp"
#include "../Sound/ISound.hpp"

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
		FF30 = 0x20,
		FF3F = 0x2F
	};
	class APU {
	public:
		APU(ISound &channelOne, ISound &channelTwo, ISound &channelThree, ISound &channelFour);
		~APU();
		APU(const APU &) = delete;
		APU &operator=(const APU &) = delete;
		void write(unsigned short, unsigned char);
		unsigned char read(unsigned short) const;
		void update(unsigned cycleNB); // retourne le nombre de cycle écoulés depuis le début du CPU
        //cycle(); // effectue un cycle

        //RegisterFunctions
        unsigned char soundModeOneCorrectRead(unsigned short) const;
        unsigned char soundModeTwoCorrectRead(unsigned short) const;
        unsigned char soundWaveCorrectRead(unsigned short) const;
		unsigned char soundNoiseCorrectRead(unsigned short) const;
		unsigned char soundControlersCorrectRead(unsigned short) const;

	private:
        ISound &_soundChannel1;    //tone and sweep
        ISound &_soundChannel2;    //only tone
        ISound &_soundChannelWave; //wave output
        ISound &_soundChannelNoise;//noise channel
		Memory _soundControllers;
		Memory _wpRAM; //wave pattern RAM
		bool _soundChanged;
	};
}


#endif //GBEMULATOR_APU_HPP
