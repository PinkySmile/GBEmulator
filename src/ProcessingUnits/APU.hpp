/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Apu.hpp
*/

#ifndef GBEMULATOR_APU_HPP
#define GBEMULATOR_APU_HPP

#define CHANSIZE_WPRAM 0xF
#define DIV_FREQUENCY 4194304

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
		WPRAM_START = 0x20,
		WPRAM_END = 0x2F
	};

	class APU {
	public:
		APU() = delete;
		APU(ISound &channelOne, ISound &channelTwo, ISound &channelThree, ISound &channelFour);
		~APU();
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

		class Sound {
		public:
			Sound() = delete;
			Sound(ISound &sound);
			~Sound() = default;
			Sound(const Sound &) = delete;
			Sound &operator=(const Sound &) = delete;

			//Common functions
			void setSweep(unsigned char);
			unsigned char getSweep() const;
			void setWave(unsigned char);
			unsigned char getWave() const;
			void setVolume(unsigned char);
			unsigned char getVolume() const;
			void setLowFrequency(unsigned char);
			void setRestartOptions(unsigned char);
			unsigned char getRestartOptions() const;

			//Wave Functions
			void setSoundONOFF(unsigned char);
			unsigned char getSoundONOFF() const;
			void setSoundLength(unsigned char, bool);
			unsigned char getSoundLength(bool) const;
			void setOutputLevel(unsigned char);
			unsigned char getOutputLevel() const;
			std::vector<unsigned char> &getWavePattern(int frequency, Memory::Memory &memory) const;

			//Noise Functions
			void updateLFSR(unsigned char stepNumber);
			static std::vector<unsigned char> &
			getNoiseWave(int frequency, unsigned char stepNumber);
			void setPolynomialCounters(unsigned char);
			unsigned char getPolynomialCounters() const;

			void update(unsigned cycle, Memory::Memory &memory);
			void updateRestart();
			void disable(bool state);

		private:
			ISound &_soundChannel;    //tone and sweep

			//sweep
			unsigned char _sweepTime = 0;
			bool _sweepDirection = 0;
			unsigned char _sweepShiftNumber = 0;
			unsigned _sweepCycles = 0;


			//wave pattern and sound duration
			unsigned char _wavePattern = 2; //chan1-2
			unsigned char _soundLength = 0;
			bool _isSixBitsLength = true;

			//volume
			unsigned char _initialVolume = 0;
			bool _volumeDirection = 0;
			unsigned char _volumeShiftNumber = 0;
			unsigned _volumeCycles = 0;

			//frequency
			unsigned short _frequency = 0;

			//options
			bool _restart = false;
			bool _restartType = false;
			bool _soundOn = false; //WAVE

			//WaveOutputLevel //WAVE
			unsigned char _waveOutputLevel = 0;

			//PolynomialCounter //NOISE
			bool _wroteInNoiseFrequency = false;
			bool _havingPolynomial = false;
			unsigned char _shiftClockFrequency = 0;
			bool _polynomialCounterStep = false;
			char _counter = 0xF;
			unsigned short _lfsr = 0x7FFF;
			unsigned char _dividingRatio = 0;
			static constexpr double dividingRatio[8] = {
					DIV_FREQUENCY / 4.,
					DIV_FREQUENCY / 8.,
					DIV_FREQUENCY / 16.,
					DIV_FREQUENCY / 24.,
					DIV_FREQUENCY / 32.,
					DIV_FREQUENCY / 40.,
					DIV_FREQUENCY / 48.,
					DIV_FREQUENCY / 56.
			};

		};

	private:
		//soundChannel1
		Sound _managerChannel1;

		//soundChannel2
		Sound _managerChannel2;    //only tone

		//soundChannelWave
		Sound _managerChannelWave; //wave output

		//soundChannelNoise
		Sound _managerChannelNoise;//noise channel

		Memory::Memory _wpRAM; //wave pattern RAM

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
