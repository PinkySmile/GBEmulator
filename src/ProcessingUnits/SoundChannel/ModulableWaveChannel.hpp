/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** ModulableWaveChannel.hpp
*/

#ifndef GBEMULATOR_MODULABLEWAVECHANNEL_HPP
#define GBEMULATOR_MODULABLEWAVECHANNEL_HPP


#include "SoundChannel.hpp"
#include "../../Memory/Memory.hpp"

#define CHANSIZE_WPRAM 0xF

namespace GBEmulator::SoundChannel
{
	class ModulableWaveChannel : public SoundChannel {
	private:
		//! @brief Wave pattern ram
		Memory::Memory _wpRAM;
		//! @brief The current wave output level
		unsigned char _waveOutputLevel = 0;
		//! @brief Whether the waves needs to be generated again.
		bool _genWave = true;

		void _update(unsigned cycles) override;
		void _checkRestart() override;

	public:
		//! @brief Constructor.
		//! @param soundInterface The interface to output the sound to.
		ModulableWaveChannel(ISound &soundInterface);

		std::vector<unsigned char> getWavePattern() const;
		unsigned char getSoundOnOff() const;
		unsigned char getSoundLength() const;
		unsigned char getOutputLevel() const;
		unsigned char read(unsigned char address) const;
		void setSoundOnOff(unsigned char);
		void setSoundLength(unsigned char);
		void setOutputLevel(unsigned char);
		void write(unsigned char address, unsigned char value);
	};
}


#endif //GBEMULATOR_MODULABLEWAVECHANNEL_HPP
