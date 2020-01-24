/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SquareWaveChannel.hpp
*/

#ifndef GBEMULATOR_SQUAREWAVECHANNEL_HPP
#define GBEMULATOR_SQUAREWAVECHANNEL_HPP


#include "SoundChannel.hpp"

namespace GBEmulator::SoundChannel
{
	//! @brief Class représentant le "Channel 1" et le "Channel 2"
	class SquareWaveChannel : public SoundChannel {
	private:
		//! @breif Les 4 formes d'onde qui peuvent être jouées
		std::vector<std::vector<unsigned char>> _waves;
		//! @breif La forme d'onde actuelle a joué.
		unsigned char _wavePattern = 0;

		void _update(unsigned cycles) override;

	public:
		//! @brief Renvoie une onde carrée;
		static std::vector<unsigned char> &getSquareWave(int frequency, float percentage);

		//! @brief Constructeurr.
		//! @param soundInterface L'interface de sortie du son..
		SquareWaveChannel(ISound &soundInterface);
		//! @brief Change la forme de l'onde.
		void setWave(unsigned char value);
		//! @brief Renvoie la forme de l'onde.
		unsigned char getWave() const;
	};
}


#endif //GBEMULATOR_SQUAREWAVECHANNEL_HPP
