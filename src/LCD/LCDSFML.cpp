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
	sf::RenderWindow(mode, title.c_str()),
	_size(160, 144),
	_screen(new sf::Color[this->_size.x * this->_size.y]),
	_framebuffer(new sf::Color[this->_size.x * this->_size.y]),
	_lastFramebuffer(new sf::Color[this->_size.x * this->_size.y]),
	_title(title),
	_view({80, 72}, {160, 144})
{
	memset(this->_framebuffer, 0, this->_size.x * this->_size.y * sizeof(*this->_framebuffer));
	memset(this->_lastFramebuffer, 0, this->_size.x * this->_size.y * sizeof(*this->_lastFramebuffer));
	this->_texture.create(this->_size.x, this->_size.y);
	this->setView(this->_view);
}

void GBEmulator::Graphics::LCDSFML::render()
{
	sf::Event event;
	sf::Sprite sprite;

	this->_texture.update(reinterpret_cast<sf::Uint8 *>(this->_lastFramebuffer));
	sprite.setTexture(this->_texture);
	sprite.setColor(sf::Color{0xFF, 0xFF, 0xFF, 0xFF});
	this->draw(sprite);
	this->_texture.update(reinterpret_cast<sf::Uint8 *>(this->_framebuffer));
	sprite.setTexture(this->_texture);
	sprite.setColor(sf::Color{0xFF, 0xFF, 0xFF, 0x80});
	this->draw(sprite);
	if (this->_clock.getElapsedTime().asMilliseconds() > 500) {
		this->setTitle((this->_title + " " + std::to_string(static_cast<int>(100 / this->_lastFrameTime / 60)) + "% (" + std::to_string(this->getFramerate()) + " FPS)").c_str());
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
	auto old = this->_lastFramebuffer;

	this->_lastFramebuffer = this->_framebuffer;
	this->_framebuffer = old;
	memcpy(this->_framebuffer, this->_screen, this->_size.x * this->_size.y * sizeof(sf::Color));
	this->_lastFrameTime = this->_emulatorSpeed.getElapsedTime().asSeconds();
	this->_emulatorSpeed.restart();
#if NO_DISPLAY_THREAD
	this->render();
#endif
}

double GBEmulator::Graphics::LCDSFML::getFramerate()
{
	return 1 / this->_fpsClock.getElapsedTime().asSeconds();
}

void GBEmulator::Graphics::LCDSFML::clear()
{
	memset(this->_screen, 0xFF, this->_size.x * this->_size.y * sizeof(*this->_screen));
	//for (unsigned i = 0; i < this->_size.x * this->_size.y; i++)
	//	this->_screen[i] = {
	//		RGBColor::White.r,
	//		RGBColor::White.g,
	//		RGBColor::White.b,
	//		255
	//	};
}

GBEmulator::Graphics::LCDSFML::~LCDSFML()
{
	delete[] this->_screen;
	delete[] this->_framebuffer;
	delete[] this->_lastFramebuffer;
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
	this->_view.setCenter(x / 2, y / 2);
	this->_view.setSize(x, y);
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