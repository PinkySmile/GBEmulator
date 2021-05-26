/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** LCDSDL.hpp
*/
#ifndef GBEMULATOR_LCDSDL_HPP
#define GBEMULATOR_LCDSDL_HPP

#include <string>
#include <SDL2/SDL.h>
#include "./ILCD.hpp"
#include "util/TimerSDL.hpp"

namespace GBEmulator::Graphics {
	class Exception : public standard::exception {
	private:
		standard::string _msg;

	public:
		Exception(const standard::string &msg) : _msg(msg) {};
		const char *what() const noexcept override { return this->_msg.c_str(); };
	};

	struct SDLVideoMode {
		int width;
		int height;
		int bpp; // bit per pixel
		Uint32 flags;
	};

	class LCDSDL : public ILCD {
	private:
		RGBColor *buffer;
		RGBColor *framebuffer;
		SDL_Window *screen;
		SDL_Texture *texture;
		SDL_Renderer *context;
		TimerSDL fps = TimerSDL();
		int frame_counter = 0;
		SDLVideoMode video_mode;

	public:
		LCDSDL();
		LCDSDL(const LCDSDL &) = delete;
		~LCDSDL();
		LCDSDL &operator =(const LCDSDL &) = delete;
		LCDSDL(SDLVideoMode mode, const standard::string &title);
		void display() override;
		void render() override;
		void clear() override;
		void setMaxSize(unsigned int x, unsigned y);
		void setPixel(unsigned int x, unsigned y, const RGBColor &color);
		bool isClosed() const override;
		void close() override;
		double getFramerate();
	};
}


#endif //GBEMULATOR_LCDSDL_HPP
