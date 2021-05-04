/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** LCDSDL.cpp
*/
#include "LCDSDL.hpp"
#define FRAMES_PER_SECOND 60
#define W 640
#define H 576

namespace GBEmulator::Graphics
{
	LCDSDL::LCDSDL() :
		LCDSDL(SDLVideoMode({640, 576, 32, SDL_SWSURFACE}), "GBEmulator")
	{}

	LCDSDL::LCDSDL(SDLVideoMode mode, const std::string &title) :
		video_mode(mode)
	{
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
			throw Exception(std::string("Can't init SDL: ") + SDL_GetError());
		this->screen = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mode.width, mode.height, SDL_WINDOW_SHOWN );
		if (this->screen == nullptr)
			throw Exception(std::string("Can't create window: ") + SDL_GetError());
		this->context = SDL_CreateRenderer(this->screen, -1, 0);
		if (this->context == nullptr)
			throw Exception(std::string("Can't create renderer: ") + SDL_GetError());
		SDL_SetRenderDrawColor(this->context, RGBColor::White.r, RGBColor::White.g, RGBColor::White.b, 255);
		this->texture = SDL_CreateTexture(this->context, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, W, H);
		if (this->texture == nullptr)
			throw Exception(std::string("Can't create texture: ") + SDL_GetError());
		this->buffer = new RGBColor[W * H];
		this->framebuffer = new RGBColor[W * H];
	}

	LCDSDL::~LCDSDL()
	{
		SDL_Quit();
	}

	void LCDSDL::display()
	{
		memcpy(this->framebuffer, this->buffer, W * H * sizeof(*this->buffer));
	}

	void LCDSDL::render()
	{
		//int ticks = fps.get_ticks();

		//this->frame_counter++;
//		if (ticks < 1000 / FRAMES_PER_SECOND) {
//			SDL_Delay((1000 / FRAMES_PER_SECOND) - ticks);
//		}
		SDL_RenderClear(this->context);
		SDL_UpdateTexture(this->texture, nullptr, this->framebuffer, W * sizeof(*this->framebuffer));
		SDL_RenderCopy(this->context, this->texture, nullptr, nullptr);
		SDL_RenderPresent(this->context);
		this->fps.reset();
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
		for (int i = 0; i < W * H; i++)
			this->buffer[i] = RGBColor::White;
	}

	void LCDSDL::setPixel(unsigned int x, unsigned y, const GBEmulator::Graphics::RGBColor &color)
	{
		x *= 4;
		y *= 4;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->buffer[(y + j) * W + (x + i)] = color;
	}

	void LCDSDL::setMaxSize(unsigned int, unsigned)
	{}
}