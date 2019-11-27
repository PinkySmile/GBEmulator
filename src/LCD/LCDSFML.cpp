/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.cpp
*/

#include <cmath>
#include "LCDSFML.hpp"

GBEmulator::Graphics::LCDSFML::LCDSFML(sf::VideoMode mode, const std::string &title) :
	sf::RenderWindow(mode, title),
	_BGTexture(0x180),
	_palette0Texture(0x180),
	_palette1Texture(0x180),
	_title(title)
{
}

void GBEmulator::Graphics::LCDSFML::display()
{
	sf::Event event;

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
	sf::RenderWindow::clear(
		sf::Color{
			RGBColor::White.r,
			RGBColor::White.g,
			RGBColor::White.b,
			255
		}
	);
}

sf::Texture& GBEmulator::Graphics::LCDSFML::_getTexture(unsigned char id, bool signedMode, TextureType type)
{
	switch (type) {
	case Background:
		if (signedMode)
			return this->_BGTexture[static_cast<char>(id) + 0x100];
		return this->_BGTexture[id];
	case Palette0:
		if (signedMode)
			return this->_palette0Texture[static_cast<char>(id) + 0x100];
		return this->_palette0Texture[id];
	case Palette1:
		if (signedMode)
			return this->_palette1Texture[static_cast<char>(id) + 0x100];
		return this->_palette1Texture[id];
	}
	return this->_BGTexture[id];
}

void GBEmulator::Graphics::LCDSFML::_getTextureFromTile(const unsigned char *tile, sf::Texture &texture, TextureType type) const
{
	sf::Color colors[64];

	texture.create(8, 8);
	switch (type) {
	case Background:
		for (int i = 0; i < 64; i++)
			colors[i] = sf::Color {
				this->_BGColorPalette[tile[i]].r,
				this->_BGColorPalette[tile[i]].g,
				this->_BGColorPalette[tile[i]].b,
				255
			};
		break;
	case Palette0:
		for (int i = 0; i < 64; i++)
			colors[i] = sf::Color {
				this->_objectColorPalette0[tile[i]].r,
				this->_objectColorPalette0[tile[i]].g,
				this->_objectColorPalette0[tile[i]].b,
				(tile[i] == 0) ? static_cast<sf::Uint8>(0) : static_cast<sf::Uint8>(255)
			};
		break;
	case Palette1:
		for (int i = 0; i < 64; i++)
			colors[i] = sf::Color {
				this->_objectColorPalette1[tile[i]].r,
				this->_objectColorPalette1[tile[i]].g,
				this->_objectColorPalette1[tile[i]].b,
				(tile[i]== 0) ? static_cast<sf::Uint8>(0) : static_cast<sf::Uint8>(255)
			};
		break;
	}
	texture.update(reinterpret_cast<sf::Uint8 *>(&colors));
}

void GBEmulator::Graphics::LCDSFML::drawBackground(const unsigned char *tiles, float x, float y, bool signedMode)
{
	sf::Vector2<double> off{fmod(x, 8), fmod(y, 8)};

	this->_sprite.setScale(1, 1);
	for (int xpos = -1; xpos < 20; xpos++)
		for (int ypos = -1; ypos < 18; ypos++) {
			int index = fmod(xpos - x / 8, 32) + 32 * static_cast<int>(fmod(ypos - y / 8, 32));

			this->_sprite.setTexture(this->_getTexture(tiles[index], signedMode, Background));
			this->_sprite.setPosition(xpos * 8 + off.x, ypos * 8 + off.y);
			this->draw(this->_sprite);
		}
}

bool GBEmulator::Graphics::LCDSFML::isClosed() const
{
	return !this->isOpen();
}

void GBEmulator::Graphics::LCDSFML::close()
{
	sf::RenderWindow::close();
}

void GBEmulator::Graphics::LCDSFML::drawWindow(const unsigned char *tiles, float x, float y, bool signedMode)
{
	this->drawBackground(tiles, x, y, signedMode);
}

void GBEmulator::Graphics::LCDSFML::updateTexture(unsigned char *tile, size_t id)
{
	this->_getTextureFromTile(tile, this->_BGTexture[id], Background);
	this->_getTextureFromTile(tile, this->_palette0Texture[id], Palette0);
	this->_getTextureFromTile(tile, this->_palette1Texture[id], Palette1);

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
		this->_sprite.setTexture(this->_getTexture(sprite.texture_id, signedMode, Palette1));
	else
		this->_sprite.setTexture(this->_getTexture(sprite.texture_id, signedMode, Palette0));
	this->_sprite.setPosition(sprite.x + sprite.x_flip * 8, sprite.y + sprite.y_flip * 8);
	this->_sprite.setScale((!sprite.x_flip * 2) - 1, (!sprite.y_flip * 2) - 1);
	this->draw(this->_sprite);
}
