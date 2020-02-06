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
         * @brief Permet d'arrêter ou de reprendre la lecture du son d'un channel de son.
         * @param disabled True -> Arrêter / False -> Reprendre
         */
        virtual void setDisabled(bool disabled) = 0;
        /*!
         * @brief Permet de changer la fréquence du son joué.
         * @param frequency Coefficient de multiplication de la fréquence du son.
         * @details Avec une fréquence du son de base à 440 Hz, si le paramètre frequency est à 1.5 par exemple, la nouvelle fréquence joué sera de 660 Hz.
         */
        virtual void setPitch(float frequency) = 0;
        /*!
         * @brief Permet de changer la forme d'onde du son.
         * @param samples La forme de l'onde sous un vecteur d'unsigned char.
         * @param sampleRate Le fréquence d'échantillonnage de l'onde
         */
        virtual void setWave(std::vector<unsigned char> samples, unsigned int sampleRate) = 0;
        /*!
         * @brief Permet de changer le volume du son joué.
         * @param volume Valeur du volume du son (de 0 à 100).
         */
        virtual void setVolume(float volume) = 0;
        /*!
         * @brief Permet de changer le volume du son joué sur la sortie SO1 (gauche).
         * @param volume Valeur du volume du son (de 0 à 100).
         */
        virtual void setSO1Volume(float volume) = 0;
        /*!
         * @brief Permet de changer le volume du son joué sur la sortie SO2 (droite).
         * @param volume Valeur du volume du son (de 0 à 100).
         */
        virtual void setSO2Volume(float volume) = 0;
    };
}


#endif //GBEMULATOR_ISOUND_HPP
