/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** LCDSDL.cpp
*/

#include <unistd.h>
#include "LCDSDL.hpp"

#ifndef __cpp_exceptions
#define throw abort(), (void)
#endif

namespace GBEmulator::Graphics
{
	LCDSDL::LCDSDL() :
		LCDSDL(SDLVideoMode({WINDOW_W, WINDOW_H, 32, SDL_SWSURFACE}), "GBEmulator")
	{}

	LCDSDL::LCDSDL(SDLVideoMode mode, const standard::string &title) :
		video_mode(mode)
	{
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
			throw Exception(standard::string("Can't init SDL video: ") + SDL_GetError());
		this->screen = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mode.width, mode.height, SDL_WINDOW_SHOWN );
		if (this->screen == nullptr)
			throw Exception(standard::string("Can't create window: ") + SDL_GetError());
		this->context = SDL_CreateRenderer(this->screen, -1, 0);
		if (this->context == nullptr)
			throw Exception(standard::string("Can't create renderer: ") + SDL_GetError());
		SDL_SetRenderDrawColor(this->context, RGBColor::White.r, RGBColor::White.g, RGBColor::White.b, 255);
		this->texture = SDL_CreateTexture(this->context, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 160, 144);
		if (this->texture == nullptr)
			throw Exception(standard::string("Can't create texture: ") + SDL_GetError());
		this->buffer = new RGBColor[160 * 144];
		this->framebuffer = new RGBColor[160 * 144];
	}

	LCDSDL::~LCDSDL()
	{
		SDL_Quit();
	}

	void LCDSDL::display()
	{
		memcpy(this->framebuffer, this->buffer, 160 * 144 * sizeof(*this->buffer));
#if NO_DISPLAY_THREAD
		this->render();
#endif
	}

	void LCDSDL::render()
	{
		SDL_RenderClear(this->context);
		SDL_UpdateTexture(this->texture, nullptr, this->framebuffer, 160 * sizeof(*this->framebuffer));
		SDL_RenderCopy(this->context, this->texture, nullptr, nullptr);
		SDL_RenderPresent(this->context);

#if !NO_DISPLAY_THREAD
		auto ticks = SDL_GetTicks();

		if (1000 / FRAMES_PER_SECOND > (ticks - this->start))
			SDL_Delay(1000 / FRAMES_PER_SECOND - (ticks - this->start));
		this->start = SDL_GetTicks();
#endif
	}

	double LCDSDL::getFramerate()
	{
		return 1 / static_cast<double>(FRAMES_PER_SECOND);
	}

	void LCDSDL::close()
	{
		SDL_DestroyWindow(this->screen);
		this->screen = nullptr;
	}

	bool LCDSDL::isClosed() const
	{
		return (this->screen == nullptr);
	}

	void LCDSDL::clear()
	{
		//for (int i = 0; i < 160 * 144; i++)
		//	this->buffer[i] = RGBColor::White;
		memset(this->buffer, 0xFF, 160 * 144 * sizeof(*this->buffer));
	}

	void LCDSDL::setPixel(unsigned int x, unsigned y, const GBEmulator::Graphics::RGBColor &color)
	{
		this->buffer[y * 160 + x] = color;
	}

	void LCDSDL::setMaxSize(unsigned int, unsigned)
	{}
}
