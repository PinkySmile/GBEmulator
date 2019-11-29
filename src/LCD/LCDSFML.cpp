/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.cpp
*/

#include <cmath>
#include <cstring>
#include "LCDSFML.hpp"

#define DUCK_TAPE(val) (((val & 1U) << 1U) | (val >> 1U))

GBEmulator::Graphics::LCDSFML::LCDSFML(sf::VideoMode mode, const std::string &title) :
	sf::RenderWindow(mode, title),
	_tiles(nullptr),
	_screen(new sf::Color[160 * 144]),
	_title(title)
{
	this->_texture.create(160, 144);
}

void GBEmulator::Graphics::LCDSFML::display()
{
	sf::Event event;
	sf::Sprite sprite;

	this->_texture.update(reinterpret_cast<sf::Uint8 *>(this->_screen));
	sprite.setTexture(this->_texture);
	this->draw(sprite);
	if (this->_clock.getElapsedTime().asMilliseconds() > 1000) {
		this->setTitle(this->_title + " (" + std::to_string(this->getFramerate()) + ") FPS");
		this->_clock.restart();
	}
	this->_fpsClock.restart();
	sf::RenderWindow::display();
	while (this->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			this->close();
	}
}

double GBEmulator::Graphics::LCDSFML::getFramerate()
{
	return 1 / this->_fpsClock.getElapsedTime().asSeconds();
}

void GBEmulator::Graphics::LCDSFML::clear()
{
	for (int i = 0; i < 160 * 144; i++)
		this->_screen[i] = {
			RGBColor::White.r,
			RGBColor::White.g,
			RGBColor::White.b,
			255
		};
	sf::RenderWindow::clear(sf::Color::White);
}

void GBEmulator::Graphics::LCDSFML::_drawTile(size_t id, int x, int y, bool swapX, bool swapY, const std::vector<RGBColor> &palette, bool transparency)
{
	unsigned char *tile = this->_tiles + id * 64;

	for (int xPos = 0; xPos < 8; xPos++)
		for (int yPos = 0; yPos < 8; yPos++)
			if (0 <= x + xPos && x + xPos < 160 && 0 <= yPos + y && yPos + y < 144) {
				auto index = tile[(!swapX ? xPos : 7 - xPos) + (!swapY ? yPos : 7 - yPos) * 8];
				auto &color = palette[DUCK_TAPE(index)];

				if (index == 0 && transparency)
					continue;

				this->_screen[x + xPos + (yPos + y) * 160] = {
					color.r,
					color.g,
					color.b,
					255
				};
			}
}

void GBEmulator::Graphics::LCDSFML::drawBackground(const unsigned char *tiles, float x, float y, bool signedMode)
{
	sf::Vector2<double> off{fmod(x, 8), fmod(y, 8)};

	for (int xpos = -1; xpos < 21; xpos++)
		for (int ypos = -1; ypos < 19; ypos++) {
			int index = fmod(xpos - x / 8, 32) + 32 * static_cast<int>(fmod(ypos - y / 8, 32));

			if (index < 0 || index > 1024)
				continue;

			this->_drawTile(
				signedMode ? static_cast<char>(tiles[index]) + 0x100: tiles[index],
				xpos * 8 + off.x,
				ypos * 8 + off.y,
				false,
				false,
				this->_BGColorPalette,
				true
			);
		}
}

void GBEmulator::Graphics::LCDSFML::drawWindow(const unsigned char *tiles, float x, float y, bool signedMode)
{
	sf::Vector2<double> off{fmod(x, 8), fmod(y, 8)};

	for (int xpos = -1; xpos < 21; xpos++)
		for (int ypos = -1; ypos < 19; ypos++) {
			int index = fmod(xpos - x / 8, 32) + 32 * static_cast<int>(fmod(ypos - y / 8, 32));

			if (index < 0 || index > 1024)
				continue;

			this->_drawTile(
				signedMode ? static_cast<char>(tiles[index]) + 0x100: tiles[index],
				xpos * 8 + off.x,
				ypos * 8 + off.y,
				false,
				false,
				this->_BGColorPalette,
				false
			);
		}
}

GBEmulator::Graphics::LCDSFML::~LCDSFML()
{
	delete[] this->_screen;
}

bool GBEmulator::Graphics::LCDSFML::isClosed() const
{
	return !this->isOpen();
}

void GBEmulator::Graphics::LCDSFML::close()
{
	sf::RenderWindow::close();
}

void GBEmulator::Graphics::LCDSFML::updateTexture(unsigned char *tile, size_t id)
{
	if (!this->_tiles)
		this->_tiles = tile - id * 64;
}

void GBEmulator::Graphics::LCDSFML::drawSprite(GBEmulator::Graphics::Sprite sprite, bool signedMode, bool doubleSize)
{
	if (doubleSize) {
		sprite.texture_id *= 4;
		sprite.x = (sprite.x + sprite.x_flip) * 4;
		sprite.y = (sprite.y + sprite.y_flip) * 4;
		for (int i = 0; i < 4; i++) {
			this->drawSprite(sprite, signedMode, false);
			sprite.x += ((!sprite.x_flip * 2) - 1) * 8;
			sprite.y += ((!sprite.y_flip * 2) - 1) * 8;
			sprite.texture_id++;
		}
		return;
	}
	if (sprite.palette_number)
		return this->_drawTile(
			signedMode ? static_cast<char>(sprite.texture_id) + 0x100 : sprite.texture_id,
			sprite.x - 8,
			sprite.y - 16,
			sprite.x_flip,
			sprite.y_flip,
			this->_objectColorPalette1,
			true
		);

	this->_drawTile(
		signedMode ? static_cast<char>(sprite.texture_id) + 0x100 : sprite.texture_id,
		sprite.x - 8,
		sprite.y - 16,
		sprite.x_flip,
		sprite.y_flip,
		this->_objectColorPalette0,
		true
	);
}
