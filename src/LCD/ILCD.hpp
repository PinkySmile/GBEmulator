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
	struct RGBColor {
		static const struct GBEmulator::Graphics::RGBColor White;
		static const struct GBEmulator::Graphics::RGBColor LGray;
		static const struct GBEmulator::Graphics::RGBColor DGray;
		static const struct GBEmulator::Graphics::RGBColor Black;

		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	class ILCD {
	public:
		friend Debugger::Debugger;
		//! Change la taille maximale de l'écran
		virtual void setMaxSize(unsigned int x, unsigned y) = 0;
		//! Change la couleur du pixel ciblé
		virtual void setPixel(unsigned int x, unsigned y, const RGBColor &color) = 0;
		//! Met à jour la fenetre du jeu
		virtual void display() = 0;
		//! Nettoie la fenetre du jeu
		virtual void clear() = 0;
		//! Renvoie True si la fenetre est fermée
		virtual bool isClosed() const = 0;
		//! Ferme la fenetre
		virtual void close() = 0;
	};
}


#endif //GBEMULATOR_ILCD_HPP