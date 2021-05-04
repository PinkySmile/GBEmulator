/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ISound.hpp
*/


#ifndef GBEMULATOR_ISOUND_HPP
#define GBEMULATOR_ISOUND_HPP

#include <vector>

namespace GBEmulator {
    /*!
     * @brief L'interface ISound implémente les fonctionnalités de lecture et de modification du son.
     * Il est ensuite utilisé par les quatre channels de sons.
     */
    class ISound {
    public:
    	virtual ~ISound() = default;
        /*!
         * @brief Permet de changer le volume du son joué.
         * @param volume Valeur du volume du son (de 0 à 100).
         */
        virtual void setVolume(float volume) = 0;
	/*!
	* @brief Ajoute des samples a jouer avec un sample rate de 44100Hz.
	* @param samples Tableau de samples.
	* @param samplesCount Nombre de samples.
	*/
        virtual void pushSamples(short *samples, size_t sampleCount) = 0;
    };
}


#endif //GBEMULATOR_ISOUND_HPP
