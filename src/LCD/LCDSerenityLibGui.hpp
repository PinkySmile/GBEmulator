//
// Created by andgel on 03/05/2021
//

#ifndef GBEMULATOR_LCDSERENITYLIBGUI_HPP
#define GBEMULATOR_LCDSERENITYLIBGUI_HPP

#include <LibGUI/Window.h>
#include <LibGfx/Bitmap.h>
#include <string>
#include "ILCD.hpp"
#include "../Timing/Clock.hpp"
#include "SerenityPlatformWindow.hpp"

namespace GBEmulator
{
	namespace Debugger
	{
		class Debugger;
	}
	namespace Graphics
	{
		class LCDSerenityLibGui : public ILCD {
		private:
			Serenity::SerenityPlatformWindow *_innerWindow;
			float                            _lastFrameTime;
			Serenity::Vector2i               _size;
			Serenity::Vector2i               _winSize;
			Gfx::Color                       *_screen;
			Gfx::Color                       *_framebuffer;
			standard::string                      _title;
			Timing::Clock                    _fpsClock;
			Timing::Clock                    _clock;
			Timing::Clock                    _emulatorSpeed;
			bool                             _closed = false;

			friend Debugger::Debugger;

		public:
			LCDSerenityLibGui() = delete;
			LCDSerenityLibGui(const LCDSerenityLibGui &) = delete;
			/*!
			 * @brief Destructeur
			 */
			~LCDSerenityLibGui() override;
			LCDSerenityLibGui &operator =(const LCDSerenityLibGui &) = delete;
			/*!
			 * @brief Constructeur
			 * @param size: Taille de la fenêtre.
			 * @param title: Titre de la fenêtre.
			 */
			LCDSerenityLibGui(Serenity::Vector2i size, const standard::string &title);
			//! Met à jour la fenetre du jeu
			void display() override;
			//! Nettoie la fenetre du jeu
			void clear() override;
			//! Change la taille maximale de l'écran
			void setMaxSize(unsigned int x, unsigned y);
			//! Change la couleur du pixel ciblé
			void setPixel(unsigned int x, unsigned y, const RGBColor &color);
			//! Renvoie True si la fenetre est fermée
			bool isClosed() const override;
			//! Ferme la fenetre
			void close() override;
			void render() override;
			/*!
			 * @brief Obtient les images par seconde
			 * @return le nombre d'ips
			 */
			double getFramerate();
		};
	}
}


#endif //GBEMULATOR_LCDSERENITYLIBGUI_HPP
