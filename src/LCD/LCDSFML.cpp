/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Lcdsfml.cpp
*/

#include <cmath>
#include <cstring>
#include "LCDSFML.hpp"

GBEmulator::Graphics::LCDSFML::LCDSFML(sf::VideoMode mode, const std::string &title) :
	sf::RenderWindow(mode, title),
	_tiles(nullptr),
	_screen(new sf::Color[160 * 144]),
	_title(title),
	_view({80, 72}, {160, 144})
{
	this->_texture.create(160, 144);
	this->setView(this->_view);
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

void GBEmulator::Graphics::LCDSFML::setMaxSize(unsigned int x, unsigned y)
{
	this->_view.setViewport({
		x / 2.f,
		y / 2.f,
		static_cast<float>(x),
		static_cast<float>(y)
	});
	this->setView(this->_view);
	this->_texture.create(x, y);
	delete[] this->_screen;
	this->_screen = new sf::Color[x * y];
}

void GBEmulator::Graphics::LCDSFML::setPixel(unsigned int x, unsigned y, const GBEmulator::Graphics::RGBColor &color)
{
	this->_screen[x + y * static_cast<unsigned>(this->_view.getSize().x)] = sf::Color{
		color.r,
		color.g,
		color.b,
		255
	};
}