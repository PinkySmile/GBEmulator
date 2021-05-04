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
	cpu{this->sound, this->screen, this->joypad, this->cableInterface, false}
{
}


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

void Tests::Screen::setMaxSize(unsigned int, unsigned int)
{

}

void Tests::Screen::setPixel(unsigned int, unsigned int,
			     const GBEmulator::Graphics::RGBColor &)
{

}

void Tests::Screen::render()
{

}


void Tests::Sound::setVolume(float)
{
}

void Tests::Sound::pushSamples(short *, size_t)
{
}

void Tests::CableInterface::_sync(unsigned int)
{

}

void Tests::CableInterface::_sendByte(unsigned char)
{

}
