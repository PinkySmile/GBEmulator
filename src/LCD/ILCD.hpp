/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** ILCD.hpp
*/

#ifndef GBEMULATOR_ILCD_HPP
#define GBEMULATOR_ILCD_HPP


#ifdef ARDUINO
#include <stdint.h>
#else
#include <cstdint>
#endif

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

		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a = 255;
		RGBColor(uint8_t r, uint8_t g, uint8_t b) noexcept;
		RGBColor(uint16_t gbc_color) noexcept;
		RGBColor(uint32_t rgba_color) noexcept;
		RGBColor() = default;
	};

	/*!
	 * @class ILCD
	 * @brief Interface ILCD qui représente l'écran
	 */
	class ILCD {
	public:
		virtual ~ILCD() = default;
		friend Debugger::Debugger;
		/*!
		 * @brief Définie la taille de l'écran
		 * @param x: largeur de l'écran.
		 * @param y: hauteur de l'écran.
		 */
		virtual void setMaxSize(unsigned x, unsigned y) = 0;
		/*!
		 * @brief Pose un pixel sur l'écran à la position x, y
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 * @param color: couleur du pixel (White, LGray, DGray, Black)
		 */
		virtual void setPixel(unsigned x, unsigned y, const RGBColor &color) = 0;
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
		/*!
		 * @brief Affiche le buffer interne à l'écran
		 */
		virtual void render() = 0;
	};
}


#endif //GBEMULATOR_ILCD_HPP