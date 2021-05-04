/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestComponents.hpp
*/
#ifndef GBEMULATOR_TESTCOMPONENTS_HPP
#define GBEMULATOR_TESTCOMPONENTS_HPP

#include <ostream>
#include "../src/Joypad/JoypadEmulator.hpp"
#include "../src/ProcessingUnits/CPU.hpp"
#include "../src/CableLink/CableInterface.hpp"


namespace Tests {
	class Joypad : public GBEmulator::Input::JoypadEmulator {
	private:
		bool _rt_value;
	public:
		Joypad(bool return_value=false);
		bool isButtonPressed(GBEmulator::Input::Keys button) const noexcept;
	};

	class Screen : public GBEmulator::Graphics::ILCD {
	private:
		bool _closed = false;

	public:
		void setMaxSize(unsigned int, unsigned int) override;
		void setPixel(unsigned int, unsigned int, const GBEmulator::Graphics::RGBColor &) override;
		void display() override;
		void clear() override;
		bool isClosed() const override;
		void close() override;
		void render() override;
	};

	class Sound : public GBEmulator::ISound {
	public:
		void pushSamples(short *samples, size_t sampleCount) override;

		void setVolume(float) override;
	};

	class CableInterface : public GBEmulator::Network::CableInterface {
	private:
		void _sync(unsigned int cycles) override;
		void _sendByte(unsigned char byte) override;
	};

	class GBTest {
	public:
		Joypad joypad;
		Screen screen;
		Sound sound;
		CableInterface cableInterface;
		GBEmulator::CPU cpu;

		GBTest();
	};
}


#endif //GBEMULATOR_TESTCOMPONENTS_HPP
