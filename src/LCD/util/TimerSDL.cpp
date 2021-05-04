/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** TimerSDL.cpp
*/

#include "TimerSDL.hpp"
#include <SDL2/SDL.h>


TimerSDL::TimerSDL()
{
	this->reset();
}

void TimerSDL::reset()
{
	startTicks = 0;
	started = false;
}

void TimerSDL::start()
{
	started = true;
	startTicks = SDL_GetTicks();
}

void TimerSDL::stop()
{
	started = false;
}

int TimerSDL::get_ticks()
{
	if(started)
	{
		return SDL_GetTicks() - startTicks;
	}
	return 0;
}

