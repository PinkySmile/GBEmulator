//
// Created by Gegel85 on 03/05/2021
//

#ifndef GBEMULATOR_CREATEINFERFACEIMPL_HPP
#define GBEMULATOR_CREATEINFERFACEIMPL_HPP

#include <string>
#include <memory>
#include "Joypad/JoypadEmulator.hpp"
#include "Sound/ISound.hpp"
#include "LCD/ILCD.hpp"
#include "CableLink/CableInterface.hpp"
#include "ProcessingUnits/CPU.hpp"

namespace GBEmulator
{
	struct Args
	{
		std::string fileName;
		std::string listenPort;
		std::string connectIp;
		bool debug = false;
		bool noDisplay = false;
		bool maxSpeed = false;
		bool noAudio = false;
		bool noBootRom = false;
		bool error = true;
		bool profiler = false;
		GBMode mode = MODE_AUTO;
	};

	struct Components {
		std::unique_ptr<GBEmulator::Network::CableInterface> network;
		std::unique_ptr<GBEmulator::ISound> sound;
		std::unique_ptr<GBEmulator::Graphics::ILCD> window;
		std::unique_ptr<GBEmulator::Input::JoypadEmulator> joypad;
	};

	Components buildComponents(const Args &args);
}

#endif //GBEMULATOR_CREATEINFERFACEIMPL_HPP
