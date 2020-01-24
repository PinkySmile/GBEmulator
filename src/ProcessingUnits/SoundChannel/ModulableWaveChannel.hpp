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
	//! @brief Class représentant le "Channel 3" permettant de modifier la forme de l'onde.
	class ModulableWaveChannel : public SoundChannel {
	private:
		//! @brief Mémoire du paterne de l'onde (Wave pattern ram)
		Memory::Memory _wpRAM;
		//! @brief Volume actuel de la sortie
		unsigned char _waveOutputLevel = 0;
		//! @brief Si les ondes doivent être générées à nouveau.
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
