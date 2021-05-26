//
// Created by Gegel85 on 03/05/2021
//

#ifndef GBEMULATOR_DUMMYDEVICES_HPP
#define GBEMULATOR_DUMMYDEVICES_HPP

#include "Joypad/JoypadEmulator.hpp"
#include "Sound/ISound.hpp"
#include "LCD/ILCD.hpp"
#include "CableLink/CableInterface.hpp"

namespace GBEmulator
{
	class DummyLCD : public GBEmulator::Graphics::ILCD {
	private:
		bool _closed = false;

	public:
		void setMaxSize(unsigned int, unsigned int) override {}
		void setPixel(unsigned int, unsigned int, const GBEmulator::Graphics::RGBColor &) override {}
		void display() override {}
		void clear() override {}
		bool isClosed() const override { return this->_closed; }
		void close() override { this->_closed = true; }
		void render() override {}
	};

	class DummyJoypadInput : public GBEmulator::Input::JoypadEmulator {
	public:
		bool isButtonPressed(GBEmulator::Input::Keys) const noexcept override { return false; }
	};

	class DummySoundPlayer : public GBEmulator::ISound {
	public:
		void pushSamples(int16_t *samples, size_t sampleCount) override{}
		void setVolume(float) override{}
	};

	class DummyCable : public Network::CableInterface {
	private:
		virtual void _sync(unsigned) {};
		virtual void _sendByte(unsigned char) {};
	};
}

#endif //GBEMULATOR_DUMMYDEVICES_HPP
