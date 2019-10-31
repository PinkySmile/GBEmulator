/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestComponents.hpp
*/
#ifndef GBEMULATOR_TESTCOMPONENTS_HPP
#define GBEMULATOR_TESTCOMPONENTS_HPP

#include <ostream>
#include "communism.hpp"
#include "../src/Joypad/JoypadEmulator.hpp"
#include "../src/ProcessingUnits/CPU.hpp"
#include "../src/Network/BgbProtocolNetworkInterface.hpp"


namespace Tests {
	class Joypad : public GBEmulator::Input::JoypadEmulator {
	private:
		bool _rt_value;
	public:
		Joypad(bool return_value=false);
		bool isButtonPressed(GBEmulator::Input::Keys button) const noexcept;
	};

	class Screen : public GBEmulator::Graphics::ILCD {
	public:
		void updateTexture(unsigned char *tile, size_t id) override;
		void drawSprite(GBEmulator::Graphics::Sprite sprite, bool signedMode, bool doubleSize) override;
		void drawBackground(const unsigned char *tiles, float x, float y, bool signedMode) override;
		void drawWindow(const unsigned char *tiles, bool signedMode) override;
		void display() override;
		void clear() override;
		bool isClosed() const override;
		void close() override;

		void setPalette(const std::vector<GBEmulator::Graphics::RGBColor> &colors);
		void setPalette(unsigned char colors);
	};

	class GBTest {
	public:
		Joypad joypad;
		Screen screen;
		GBEmulator::Network::BGBProtocolCableInterface cableInterface;
		GBEmulator::CPU cpu;

		GBTest();
	};
}


#endif //GBEMULATOR_TESTCOMPONENTS_HPP
