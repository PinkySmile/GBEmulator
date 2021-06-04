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
	namespace Debugger {
		class Debugger;
	}

	enum NoiseWaveChannelInternalRegisters {
		NOISE_CHANNEL_SOUND_LENGTH = 1,
		NOISE_CHANNEL_VOLUME,
		NOISE_CHANNEL_POLYNOMIAL_COUNTER,
		NOISE_CHANNEL_COUNTER_CONSEC_INITIAL,
	};

	class NoiseWaveChannel : public BasicSoundChannel {
	private:
		struct VolumeEnvelopeRegister {
			uint8_t numberOfSweeps : 3;
			bool increases : 1;
			uint8_t initialVolume : 4;

			VolumeEnvelopeRegister(uint8_t v) { *this = v; };
			VolumeEnvelopeRegister &operator=(uint8_t v) { *reinterpret_cast<uint8_t *>(this) = v; return *this; }
			operator uint8_t() const { return *reinterpret_cast<const uint8_t *>(this); }
		};

		struct PolynomialCounterRegister {
			uint8_t dividingRatio : 3;
			bool isCounter7bits : 1;
			uint8_t shiftClockFrequency : 4;

			PolynomialCounterRegister(uint8_t v) { *this = v; };
			PolynomialCounterRegister &operator=(uint8_t v) { *reinterpret_cast<uint8_t *>(this) = v; return *this; }
			operator uint8_t() const { return *reinterpret_cast<const uint8_t *>(this); }
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
		uint8_t _length : 6;
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
		uint8_t read(unsigned int relativeAddress) override;

		void onPowerOff() override;

		friend Debugger::Debugger;
	};
}


#endif //GBEMULATOR_NOISEWAVECHANNEL_HPP
