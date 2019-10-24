/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.cpp
*/

#include "LCDSFML.hpp"

GBEmulator::Graphics::LCDSFML::LCDSFML(sf::VideoMode mode, const std::string &title) :
	sf::RenderWindow(mode, title)
{
}

void GBEmulator::Graphics::LCDSFML::write(GBEmulator::Graphics::Sprite sprite) {
	sf::Sprite s;

	this->_texture.push_back(this->getTextureFromTile(sprite.tile, sprite.priority));
	s.setTexture(this->_texture.back());
	s.setPosition(sprite.x, sprite.y);
	if (sprite.x_flip)
		s.setScale(-1, 1);
	if (sprite.y_flip)
		s.setScale(1, -1);

	if (sprite.priority)
		this->_forground.push_back(s);
	else
		this->_background.push_back(s);
}

void GBEmulator::Graphics::LCDSFML::display() {
	for (auto &sprite : this->_background)
		this->draw(sprite);
	for (auto &sprite : this->_forground)
		this->draw(sprite);
	this->_texture.clear();
	this->_background.clear();
	this->_forground.clear();
	sf::RenderWindow::display();
}

sf::Texture GBEmulator::Graphics::LCDSFML::getTextureFromTile(std::vector<int> tile, bool forground) const {
	sf::Texture texture;
	auto *pixels = new sf::Uint8[8 * 8 * 4];

	texture.create(8, 8);
	for (int i = 0; i < 64; i++) {
		pixels[0 + i * 4] = this->_colors[tile[i]].r;
		pixels[1 + i * 4] = this->_colors[tile[i]].g;
		pixels[2 + i * 4] = this->_colors[tile[i]].b;
		if (tile[i] == 0 && forground)
			pixels[3 + i * 4] = 0;
		else
			pixels[3 + i * 4] = this->_colors[tile[i]].a;
	}
	texture.update(pixels);
	delete[] pixels;
	return texture;
}

