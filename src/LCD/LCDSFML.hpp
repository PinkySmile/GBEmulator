/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.hpp
*/

#ifndef GBEMULATOR_LCDSFML_HPP
#define GBEMULATOR_LCDSFML_HPP

#include "ILCD.hpp"

namespace GBEmulator
{
	namespace Debugger {
		class Debugger;
	}
	namespace Graphics {
		/*!
		 * @class LCDSFML
		 * @brief Implémentation de ILCD avec la SFML
		 */
		class LCDSFML : public ILCD, public sf::RenderWindow {
		private:
			sf::Vector2u  _size;
			sf::Color     *_screen;
			sf::Color     *_framebuffer;
			std::string   _title;
			sf::Clock     _fpsClock;
			sf::Clock     _clock;
			sf::Texture   _texture;
			sf::View      _view;
			bool          _closed = false;

			friend Debugger::Debugger;

		public:
			LCDSFML() = delete;
			LCDSFML(const LCDSFML &) = delete;
			/*!
			 * @brief Destructeur
			 */
			~LCDSFML() override;
			LCDSFML &operator =(const LCDSFML &) = delete;
			/*!
			 * @brief Constructeur
			 * @param mode: VideoMode SFML.
			 * @param title: Titre de la fenêtre.
			 */
			LCDSFML(sf::VideoMode mode, const std::string &title);
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

#endif //GBEMULATOR_LCDSFML_HPP
