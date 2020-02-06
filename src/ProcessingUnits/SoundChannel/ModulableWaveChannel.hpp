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

#define CHANSIZE_WPRAM 16

namespace GBEmulator::SoundChannel
{
	//! @brief Classe représentant le Channel Wave permettant de modifier la forme de l'onde jouée.
	class ModulableWaveChannel : public SoundChannel {
	private:
		//! @brief Mémoire de la forme de l'onde (Wave pattern ram)
		Memory::Memory _wpRAM;
		//! @brief Volume actuel de la sortie
		unsigned char _waveOutputLevel = 0;
		//! @brief Si les ondes doivent être générées à nouveau.
		bool _genWave = true;

		void _update(unsigned cycles) override;
		void _checkRestart() override;

	public:
		//! @brief Constructeur.
		//! A l'initialisation, lance un son en volume 0.
		//! @param soundInterface L'interface de son utilisé pour jouer le son construit par ce channel.
		ModulableWaveChannel(ISound &soundInterface);

		/*!
		 * @brief Permet de récupérer la forme de l'onde présent dans la mémoire WPRam
		 * @return Le vecteur d'unsigned char représentant la forme de l'onde présent dans la mémoire WPRam
		 */
		std::vector<unsigned char> getWavePattern() const;
		/*!
		 * @brief Permet de récupérer l'état de lecture du son du channel.
		 * @return On = True, Off = False
		 */
		unsigned char getSoundOnOff() const;
		/*!
		 * @brief Permet de récupérer la longueur du son joué.
		 * @return Longueur du son joué (8 bits)
		 */
		unsigned char getSoundLength() const;
		/*!
		 * @brief Permet de récupérer le niveau du volume de la wave (sur 2 bits).
		 * @return Le niveau du volume de la wave.
		 */
		unsigned char getOutputLevel() const;
		/*!
		 * Permet de lire dans le channel wave à l'adresse indiquée
		 * @param address Adresse de lecture dans le channel wave
		 * @return La valeur écrite à l'adresse renseignée.
		 */
		unsigned char read(unsigned char address) const;
		/*!
		 * @brief Permet de changer l'état de lecture du son du channel.
		 * @param value Le byte concernant le registre du SoundOnOff.
		 */
		void setSoundOnOff(unsigned char value);
		/*!
		 * @brief Permet de changer la longueur du son joué
		 * @param length Longueur du son joué (8 bits)
		 */
		void setSoundLength(unsigned char length);
		/*!
		 * @brief Permet de changer le volume de sortie de la wave du channel wave.
		 * @param level Sur 2 bits (5-6), le niveau de volume du channel.
		 */
		void setOutputLevel(unsigned char level);
		/*!
		 * @brief Permet d'écrire dans le channel wave à l'adresse indiquée.
		 * @param address Adresse d'écriture dans le channel wave.
		 * @param value Valeur à écrire dans le channel wave.
		 */
		void write(unsigned char address, unsigned char value);
	};
}


#endif //GBEMULATOR_MODULABLEWAVECHANNEL_HPP
