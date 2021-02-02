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
		void setDisabled(bool) override;
		void setPitch(float) override;
		void setWave(std::vector<unsigned char>, unsigned int) override;
		void setVolume(float) override;
		void setSO1Volume(float) override;
		void setSO2Volume(float) override;
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
		Sound sound1;
		Sound sound2;
		Sound sound3;
		Sound sound4;
		CableInterface cableInterface;
		GBEmulator::CPU cpu;

		GBTest();
	};
}


#endif //GBEMULATOR_TESTCOMPONENTS_HPP
