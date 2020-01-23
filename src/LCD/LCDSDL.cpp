/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** LCDSDL.cpp
*/
#include "LCDSDL.hpp"
#define FRAMES_PER_SECOND 60

namespace GBEmulator::Graphics {
	LCDSDL::LCDSDL() :
			LCDSDL(SDLVideoMode({640, 576, 32, SDL_SWSURFACE}), "GBEmulator")
	{}

	LCDSDL::LCDSDL(SDLVideoMode mode, const std::string &title) :
			video_mode(mode)
	{
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
			throw Exception(std::string("Can't init SDL: ") + SDL_GetError());
		this->screen = SDL_SetVideoMode(mode.width, mode.height, mode.bpp, mode.flags);
		if (this->screen == nullptr)
			throw Exception(std::string("Can't set video mode: ") + SDL_GetError());
	}

	LCDSDL::~LCDSDL()
	{
		SDL_Quit();
	}

	void LCDSDL::display()
	{
		int ticks = fps.get_ticks();

		this->frame_counter++;
//		if (ticks < 1000 / FRAMES_PER_SECOND) {
//			SDL_Delay((1000 / FRAMES_PER_SECOND) - ticks);
//		}
		SDL_Flip(screen);
		this->fps.reset();
	}

	double LCDSDL::getFramerate()
	{
		return static_cast<double>(FRAMES_PER_SECOND);
	}

	void LCDSDL::close()
	{
		SDL_Quit();
	}

	bool LCDSDL::isClosed() const
	{
		return (this->screen == nullptr);
	}

	void LCDSDL::clear()
	{
		SDL_FillRect(this->screen, nullptr, 0x000000);
	}

	void LCDSDL::setPixel(unsigned int x, unsigned y, const GBEmulator::Graphics::RGBColor &color)
	{
		Uint32 *pixels = static_cast<Uint32 *>(this->screen->pixels);
		Uint32 col = RGBAColor(color);

		x *= 4;
		y *= 4;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				pixels[(y + j) * video_mode.width + (x + i)] = col;
	}

	RGBAColor::RGBAColor(const GBEmulator::Graphics::RGBColor &color):
			r(color.r),
			g(color.g),
			b(color.b),
			a(0xFF)
	{}

	void LCDSDL::setMaxSize(unsigned int, unsigned)
	{}
}