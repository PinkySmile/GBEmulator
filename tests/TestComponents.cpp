/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestComponents.cpp
*/
#include "TestComponents.hpp"

Tests::Joypad::Joypad(bool return_value):
	_rt_value(return_value)
{}

bool Tests::Joypad::isButtonPressed(GBEmulator::Input::Keys) const noexcept
{
	return this->_rt_value;
}

Tests::GBTest::GBTest() :
	cpu{this->sound1, this->sound2, this->sound3, this->sound4, this->screen, this->joypad, this->cableInterface}
{
}


void Tests::Screen::updateTexture(unsigned char *, size_t)
{}

bool Tests::Screen::isClosed() const
{
	return false;
}

void Tests::Screen::clear()
{}

void Tests::Screen::close()
{}

void Tests::Screen::display()
{}

void Tests::Screen::drawBackground(const unsigned char *, float, float, bool)
{}

void Tests::Screen::drawSprite(GBEmulator::Graphics::Sprite, bool, bool)
{}

void Tests::Screen::drawWindow(const unsigned char *, float, float, bool)
{}

void Tests::Sound::setPitch(float)
{
}

void Tests::Sound::setWave(std::vector<unsigned char>, unsigned int)
{
}

void Tests::Sound::setVolume(float)
{
}

void Tests::Sound::setDisabled(bool)
{}