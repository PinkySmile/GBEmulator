/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** LCDSDL.cpp
*/
#include "LCDSDL.hpp"
#define FRAMES_PER_SECOND 60

namespace GBEmulator::Graphics {
	LCDSDL::LCDSDL():
		LCDSDL(SDLVideoMode({640, 576, 16, SDL_SWSURFACE}), "GBEmulator")
	{}

	LCDSDL::LCDSDL(SDLVideoMode mode, const std::string &title)
	{
		if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
			throw Exception(std::string("Can't init SDL: ") + SDL_GetError());
		this->screen = SDL_SetVideoMode(mode.width, mode.height, mode.bpp, mode.flags);
		if(this->screen == nullptr)
			throw Exception(std::string("Can't set video mode: ") + SDL_GetError( ) );
	}

	LCDSDL::~LCDSDL()
	{
		SDL_Quit();
	}

	void LCDSDL::display() {
		int ticks = fps.get_ticks();

		this->frame_counter++;
		if(ticks < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - ticks);
		}
	}

	void LCDSDL::capFPS()
	{

	}
}