//
// Created by andgel on 05/05/2021
//

#ifndef GBEMULATOR_SQUAREWAVECHANNEL_HPP
#define GBEMULATOR_SQUAREWAVECHANNEL_HPP


#include "BasicSoundChannel.hpp"

namespace GBEmulator
{
	enum SquareWaveChannelInternalRegisters {
		SQUARE_CHANNEL_SWEEP_REGISTER,
		SQUARE_CHANNEL_SOUND_LENGTH_WAVE_PATTERN_DUTY,
		SQUARE_CHANNEL_VOLUME_ENVELOPE,
		SQUARE_CHANNEL_FREQUENCY_LO,
		SQUARE_CHANNEL_FREQUENCY_HI,
	};

	class SquareWaveChannel : public BasicSoundChannel {
	private:
		enum PatternDuty {
			DUTY_12_5_PERCENT,
			DUTY_25_PERCENT,
			DUTY_50_PERCENT,
			DUTY_75_PERCENT,
		};

		struct SweepRegister {
			unsigned char sweepShifts : 3;
			bool substract : 1;
			unsigned char sweepTime : 3;
			unsigned char _ : 1;

			SweepRegister(unsigned char v) { *this = v; };
			SweepRegister &operator=(unsigned char v) {
				*reinterpret_cast<unsigned char *>(this) = v;
				this->_ = 1;
				return *this;
			}
			operator unsigned char() const { return *reinterpret_cast<const unsigned char *>(this); }
		};

		struct SoundLenPatternDutyRegister {
			unsigned char length : 6;
			PatternDuty patternDuty : 2;

			SoundLenPatternDutyRegister(unsigned char v) { *this = v; };
			SoundLenPatternDutyRegister &operator=(unsigned char v) { *reinterpret_cast<unsigned char *>(this) = v; return *this; }
			operator unsigned char() const { return *reinterpret_cast<const unsigned char *>(this) | 0x3F; }
		};

		struct VolumeEnvelopeRegister {
			unsigned char numberOfSweeps : 3;
			bool increases : 1;
			unsigned char initialVolume : 4;

			VolumeEnvelopeRegister(unsigned char v) { *this = v; };
			VolumeEnvelopeRegister &operator=(unsigned char v) { *reinterpret_cast<unsigned char *>(this) = v; return *this; }
			operator unsigned char() const { return *reinterpret_cast<const unsigned char *>(this); }
		};

		struct FrequencyRegister {
			uint8_t loFrequency;
			union {
				uint8_t highByte;
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
			void setActualFrequency(float frequ) { this->setFrequency(2048.f - 131072.f / frequ); };
			float getActualFrequency() const { return 131072.f / (2048.f - this->getFrequency()); };
		};

		void _restart();
		void _update(unsigned cycles) override;
		uint16_t _getSoundData() const override;

		SweepRegister               _sweepRegister = 0;
		SoundLenPatternDutyRegister _soundLenPatternDutyRegister = 0;
		VolumeEnvelopeRegister      _volumeEnvelopeRegister = 0;
		VolumeEnvelopeRegister      _effectiveVolumeEnvelopeRegister = 0;
		FrequencyRegister           _frequencyRegister = 0;

		uint16_t _sweepFrequencyShadow = 0;

		double _lengthCounter = 0;
		double _frequencyCounter = 0;
		double _volumeEnvelopeCounter = 0;
		double _frequencySweepCounter = 0;

	public:
		void write(unsigned int relativeAddress, uint8_t value) override;
		unsigned char read(unsigned int relativeAddress) override;

		void onPowerOff() override;
	};
}


#endif //GBEMULATOR_SQUAREWAVECHANNEL_HPP
