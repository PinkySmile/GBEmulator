//
// Created by andgel on 05/05/2021
//

#ifndef GBEMULATOR_MODULABLEWAVECHANNEL_HPP
#define GBEMULATOR_MODULABLEWAVECHANNEL_HPP


#include "BasicSoundChannel.hpp"

namespace GBEmulator
{
	enum ModulableWaveChannelInternalRegisters {
		MODULABLE_CHANNEL_ON_OFF,
		MODULABLE_CHANNEL_SOUND_LENGTH,
		MODULABLE_CHANNEL_VOLUME,
		MODULABLE_CHANNEL_FREQUENCY_LO,
		MODULABLE_CHANNEL_FREQUENCY_HI,
		MODULABLE_CHANNEL_WPRAM_START = 22,
		MODULABLE_CHANNEL_WPRAM_END = 37,
	};

	class ModulableWaveChannel : public BasicSoundChannel {
	private:
		enum OutputLevel {
			OUTPUT_MUTED,
			OUTPUT_100_PERCENT,
			OUTPUT_50_PERCENT,
			OUTPUT_25_PERCENT,
		};

		struct FrequencyRegister {
			unsigned char loFrequency;
			union {
				unsigned char highByte;
				struct {
					unsigned char hiFrequency : 3;
					unsigned char _ : 3;
					bool useLength: 1;
					bool initial : 1;
				};
			};

			FrequencyRegister(unsigned short v) { *reinterpret_cast<unsigned short *>(this) = v; };
			void setHigh(unsigned char v) { this->highByte = v; this->_ = 0x7; }
			unsigned char getHigh() const  { return this->highByte | 0xBF; }
			void setFrequency(unsigned short frequ) {
				FrequencyRegister temp = frequ;

				this->loFrequency = temp.loFrequency;
				this->hiFrequency = temp.hiFrequency;
			};
			unsigned short getFrequency() const { return *reinterpret_cast<const unsigned short *>(this) & 0x07FF; };
			void setActualFrequency(float frequ) { this->setFrequency(2048.f - 65536.f / frequ); };
			float getActualFrequency() const { return 65536.f / (2048.f - this->getFrequency()); };
		};

		bool _enabled = false;
		unsigned char _length = 0;
		unsigned char _wpram[0x20];
		OutputLevel _volume = OUTPUT_MUTED;
		FrequencyRegister _frequencyRegister = 0;
		unsigned char _current = 0;
		double _nextByteCounter = 0;
		double _lengthCounter = 0;

		void _update(unsigned cycles) override;
		short _getSoundData() const override;
		void _restart();
	public:
		void write(unsigned int relativeAddress, unsigned char value) override;
		unsigned char read(unsigned int relativeAddress) override;
	};
}


#endif //GBEMULATOR_MODULABLEWAVECHANNEL_HPP
