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
	_size(160, 144),
	_screen(new sf::Color[this->_size.x * this->_size.y]),
	_framebuffer(new sf::Color[this->_size.x * this->_size.y]),
	_title(title),
	_view({80, 72}, {160, 144})
{
	this->_texture.create(this->_size.x, this->_size.y);
	this->setView(this->_view);
}

void GBEmulator::Graphics::LCDSFML::render()
{
	sf::Event event;
	sf::Sprite sprite;

	this->_texture.update(reinterpret_cast<sf::Uint8 *>(this->_framebuffer));
	sprite.setTexture(this->_texture);
	this->draw(sprite);
	if (this->_clock.getElapsedTime().asMilliseconds() > 500) {
		this->setTitle(this->_title + " " + std::to_string(static_cast<int>(100 / this->_lastFrameTime / 60)) + "% (" + std::to_string(this->getFramerate()) + " FPS)");
		this->_clock.restart();
	}
	this->_fpsClock.restart();
	sf::RenderWindow::display();
	while (this->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			this->close();
	}
}

void GBEmulator::Graphics::LCDSFML::display()
{
	std::memcpy(this->_framebuffer, this->_screen, this->_size.x * this->_size.y * sizeof(sf::Color));
	this->_lastFrameTime = this->_emulatorSpeed.getElapsedTime().asSeconds();
	this->_emulatorSpeed.restart();
}

double GBEmulator::Graphics::LCDSFML::getFramerate()
{
	return 1 / this->_fpsClock.getElapsedTime().asSeconds();
}

void GBEmulator::Graphics::LCDSFML::clear()
{
	for (unsigned i = 0; i < this->_size.x * this->_size.y; i++)
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
	delete[] this->_framebuffer;
}

bool GBEmulator::Graphics::LCDSFML::isClosed() const
{
	return this->_closed;
}

void GBEmulator::Graphics::LCDSFML::close()
{
	this->_closed = true;
	sf::RenderWindow::close();
}

void GBEmulator::Graphics::LCDSFML::setMaxSize(unsigned int x, unsigned y)
{
	this->_size = {x, y};
	this->_view.setViewport({
		x / 2.f,
		y / 2.f,
		static_cast<float>(x),
		static_cast<float>(y)
	});
	this->setView(this->_view);
	this->_texture.create(x, y);
	delete[] this->_screen;
	delete[] this->_framebuffer;
	this->_screen = new sf::Color[x * y];
	this->_framebuffer = new sf::Color[x * y];
}

void GBEmulator::Graphics::LCDSFML::setPixel(unsigned int x, unsigned y, const GBEmulator::Graphics::RGBColor &color)
{
	this->_screen[x + y * this->_size.x] = sf::Color{
		color.r,
		color.g,
		color.b,
		255
	};
}