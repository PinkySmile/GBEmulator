/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.cpp
*/

#include "LCDSFML.hpp"

GBEmulator::Graphics::LCDSFML::LCDSFML(sf::VideoMode mode, const std::string &title) :
	sf::RenderWindow(mode, title),
	_texture(512),
	_title(title)
{
}

void GBEmulator::Graphics::LCDSFML::display() {
	if (this->_clock.getElapsedTime().asMilliseconds() > 1000) {
		this->setTitle(this->_title + " (" + std::to_string(this->getFramerate()) + ") FPS");
		this->_clock.restart();
	}
	this->_fpsClock.restart();
	sf::RenderWindow::display();
	this->clear(this->_colors[0]);
}

double GBEmulator::Graphics::LCDSFML::getFramerate()
{
	return 1 / this->_fpsClock.getElapsedTime().asSeconds();
}

void GBEmulator::Graphics::LCDSFML::_getTextureFromTile(unsigned char *tile, sf::Texture &texture) const {
	auto *pixels = new sf::Uint8[8 * 8 * 4];

	texture.create(8, 8);
	for (int i = 0; i < 64; i++) {
		pixels[0 + i * 4] = this->_colors[tile[i]].r;
		pixels[1 + i * 4] = this->_colors[tile[i]].g;
		pixels[2 + i * 4] = this->_colors[tile[i]].b;
		pixels[3 + i * 4] = this->_colors[tile[i]].a;
	}
	texture.update(pixels);
	delete[] pixels;
}

void GBEmulator::Graphics::LCDSFML::updateTexture(unsigned char *tile, size_t id) {
	this->_getTextureFromTile(tile, this->_texture[id]);
}

void GBEmulator::Graphics::LCDSFML::drawSprite(GBEmulator::Graphics::Sprite sprite) {
	this->_sprite.setTexture(this->_texture[sprite.texture_id]);
	this->_sprite.setPosition(sprite.x + sprite.x_flip * 8, sprite.y + sprite.y_flip * 8);
	this->_sprite.setScale((!sprite.x_flip * 2) - 1, (!sprite.y_flip * 2) - 1);
	this->draw(this->_sprite);
}

