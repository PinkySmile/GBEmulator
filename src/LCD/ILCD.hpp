/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ILCD.hpp
*/

#ifndef GBEMULATOR_ILCD_HPP
#define GBEMULATOR_ILCD_HPP

#include <SFML/Graphics.hpp>
#include <vector>

namespace GBEmulator::Debugger {
	class Debugger;
}

namespace GBEmulator::Graphics
{
	/*!
	 * @struct RGBColor
	 * @brief Couleur d'affichage du LCD
	 */
	struct RGBColor {
		static const struct GBEmulator::Graphics::RGBColor White;
		static const struct GBEmulator::Graphics::RGBColor LGray;
		static const struct GBEmulator::Graphics::RGBColor DGray;
		static const struct GBEmulator::Graphics::RGBColor Black;

		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	/*!
	 * @class ILCD
	 * @brief Interface ILCD qui représente l'écran
	 */
	class ILCD {
	public:
		friend Debugger::Debugger;
		/*!
		 * @brief Définie la taille de l'écran
		 * @param x: largeur de l'écran.
		 * @param y: hauteur de l'écran.
		 */
		virtual void setMaxSize(unsigned int x, unsigned y) = 0;
		/*!
		 * @brief Pose un pixel sur l'écran à la position x, y
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 * @param color: couleur du pixel (White, LGray, DGray, Black)
		 */
		virtual void setPixel(unsigned int x, unsigned y, const RGBColor &color) = 0;
		/*!
		 * @brief Affiche l'écran mis àa jour
		 */
		virtual void display() = 0;
		/*!
		 * @brief Efface l'écran
		 */
		virtual void clear() = 0;
		/*!
		 * @brief Si la fenêtre est fermée
		 * @return true si fermée
		 */
		virtual bool isClosed() const = 0;
		/*!
		 * @brief Ferme la fenêtre
		 */
		virtual void close() = 0;
	};
}


#endif //GBEMULATOR_ILCD_HPP