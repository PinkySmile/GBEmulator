//
// Created by andgel on 06/05/2021
//

#ifndef GBEMULATOR_NOISEWAVECHANNEL_HPP
#define GBEMULATOR_NOISEWAVECHANNEL_HPP


#ifndef ARDUINO
#include <cmath>
#include <cstdint>
#else
#include <math.h>
#include <stdint.h>
#endif
#include "BasicSoundChannel.hpp"

namespace GBEmulator
{
	enum NoiseWaveChannelInternalRegisters {
		NOISE_CHANNEL_SOUND_LENGTH = 1,
		NOISE_CHANNEL_VOLUME,
		NOISE_CHANNEL_POLYNOMIAL_COUNTER,
		NOISE_CHANNEL_COUNTER_CONSEC_INITIAL,
	};

	class NoiseWaveChannel : public BasicSoundChannel {
	private:
		/*
		FF22 - NR43 - Channel 4 Polynomial Counter (R/W)
		The amplitude is randomly switched between high and low at the given frequency. A higher frequency will make the noise to appear 'softer'.
		When Bit 3 is set, the output will become more regular, and some frequencies will sound more like Tone than Noise.
		  Bit 7-4 - Shift Clock Frequency (s)
		  Bit 3   - Counter Step/Width (0=15 bits, 1=7 bits)
		  Bit 2-0 - Dividing Ratio of Frequencies (r)
		Frequency = 524288 Hz / r / 2^(s+1) ;For r=0 assume r=0.5 instead*/
		struct VolumeEnvelopeRegister {
			unsigned char numberOfSweeps : 3;
			bool increases : 1;
			unsigned char initialVolume : 4;

			VolumeEnvelopeRegister(unsigned char v) { *this = v; };
			VolumeEnvelopeRegister &operator=(unsigned char v) { *reinterpret_cast<unsigned char *>(this) = v; return *this; }
			operator unsigned char() const { return *reinterpret_cast<const unsigned char *>(this); }
		};

		struct PolynomialCounterRegister {
			unsigned char dividingRatio : 3;
			bool isCounter7bits : 1;
			unsigned char shiftClockFrequency : 4;

			PolynomialCounterRegister(unsigned char v) { *this = v; };
			PolynomialCounterRegister &operator=(unsigned char v) { *reinterpret_cast<unsigned char *>(this) = v; return *this; }
			operator unsigned char() const { return *reinterpret_cast<const unsigned char *>(this); }
			double getFrequency() const {
				double r = this->dividingRatio;

				if (r == 0)
					r = 0.5;
				return (524288. / r / pow(2, this->shiftClockFrequency + 1));
			}
		};

		VolumeEnvelopeRegister _volumeEnvelopeRegister = 0;
		VolumeEnvelopeRegister _effectiveVolumeEnvelopeRegister = 0;
		PolynomialCounterRegister _polynomialCounter = 0;
		unsigned short _lfsr : 15;
		unsigned char _length : 7;
		bool _initial : 1;
		bool _useLength : 1;
		double _lengthCounter = 0;

		double _lfsrCounter = 0;
		double _volumeEnvelopeCounter = 0;

		void _restart();
		void _update(unsigned cycles) override;
		uint16_t _getSoundData() const override;

	public:
		NoiseWaveChannel();
		void write(unsigned int relativeAddress, uint8_t value) override;
		unsigned char read(unsigned int relativeAddress) override;

		void onPowerOff() override;
	};
}


#endif //GBEMULATOR_NOISEWAVECHANNEL_HPP
