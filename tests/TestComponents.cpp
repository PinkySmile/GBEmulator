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

bool Tests::Joypad::isButtonPressed(Tests::Keys) const noexcept
{
	return this->_rt_value;
}