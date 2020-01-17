/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** LCDSDL.hpp
*/
#ifndef GBEMULATOR_LCDSDL_HPP
#define GBEMULATOR_LCDSDL_HPP

#include "./ILCD.hpp"
#include "util/TimerSDL.hpp"
#include <SDL/SDL.h>

namespace GBEmulator
{
	namespace Debugger {
		class Debugger;
	}
	namespace Graphics {
		class Exception : public std::exception {
		private:
			std::string _msg;

		public:
			Exception(const std::string &msg) : _msg(msg) {};
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
			SDL_Surface *screen;
			TimerSDL fps = TimerSDL();
			int frame_counter = 0;

			friend Debugger::Debugger;
		public:
			LCDSDL();
			LCDSDL(const LCDSDL &) = delete;
			~LCDSDL();
			LCDSDL &operator =(const LCDSDL &) = delete;
			LCDSDL(SDLVideoMode mode, const std::string &title);
			void display() override;
			void clear() override;
			void setMaxSize(unsigned int x, unsigned y);
			void setPixel(unsigned int x, unsigned y, const RGBColor &color);
			bool isClosed() const override;
			void close() override;
			double getFramerate();
			void capFPS();
		};
	}
}


#endif //GBEMULATOR_LCDSDL_HPP
