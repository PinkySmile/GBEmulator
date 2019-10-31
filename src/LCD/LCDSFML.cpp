/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.cpp
*/

#include "LCDSFML.hpp"

GBEmulator::Graphics::LCDSFML::LCDSFML(sf::VideoMode mode, const std::string &title) :
	sf::RenderWindow(mode, title),
	_texture(0x180),
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

sf::Texture& GBEmulator::Graphics::LCDSFML::_getTexture(unsigned char id, bool signedMode)
{
	if (signedMode)
		return this->_texture[static_cast<char>(id) + 0x100];
	return this->_texture[id];
}

void GBEmulator::Graphics::LCDSFML::_getTextureFromTile(const unsigned char *tile, sf::Texture &texture) const
{
	sf::Color colors[64];

	texture.create(8, 8);
	for (int i = 0; i < 64; i++)
		colors[i] = sf::Color{
			this->_colorPalette[tile[i]].r,
			this->_colorPalette[tile[i]].g,
			this->_colorPalette[tile[i]].b,
			255
		};
	texture.update(reinterpret_cast<sf::Uint8 *>(&colors));
}

void GBEmulator::Graphics::LCDSFML::drawBackground(const unsigned char *tiles, float x, float y, bool signedMode)
{
	for (unsigned i = 0; i < 1024; i++) {
		this->_sprite.setTexture(this->_getTexture(tiles[i], signedMode));
		this->_sprite.setPosition(x + i % 32 * 8, y + i / 32 * 8);
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
	this->_getTextureFromTile(tile, this->_texture[id]);
}

void GBEmulator::Graphics::LCDSFML::drawSprite(GBEmulator::Graphics::Sprite sprite, bool signedMode, bool doubleSize)
{
	if (doubleSize) {
		sprite.texture_id *= 4;
		sprite.x = (sprite.x + !sprite.x_flip) * 4;
		sprite.y = (sprite.y + !sprite.y_flip) * 4;
		for (int i = 0; i < 4; i++) {
			this->drawSprite(sprite, signedMode, false);
			sprite.x += ((sprite.x_flip * 2) - 1) * 8;
			sprite.y += ((sprite.x_flip * 2) - 1) * 8;
			sprite.texture_id++;
		}
		return;
	}
	this->_sprite.setTexture(this->_getTexture(sprite.texture_id, signedMode));
	this->_sprite.setPosition(sprite.x + !sprite.x_flip * 8, sprite.y + !sprite.y_flip * 8);
	this->_sprite.setScale((sprite.x_flip * 2) - 1, (sprite.y_flip * 2) - 1);
	this->draw(this->_sprite);
}
