//
// Created by Gegel85 on 03/05/2021
//

#include <stdexcept>
#include "CreateInferfaceImpl.hpp"
#include "DummyDevices.hpp"

#if SFML_IMPL
#include "CableLink/BgbProtocolNetworkInterface.hpp"
#include "LCD/LCDSFML.hpp"
#include "Joypad/SfmlKeyboardJoypadEmulator.hpp"
#include "Sound/SFMLSoundPlayer.hpp"

#elif SERENITY_IMPL
#include "LCD/LCDSerenityLibGui.hpp"
#elif SDL_IMPL
#include "LCD/LCDSDL.hpp"
#include "Joypad/SDLKeyboardJoypadEmulator.hpp"
#endif

namespace GBEmulator
{
	Input::JoypadEmulator *createJoypadEmulatorImpl(Components &otherComponents, const Args &args)
	{
		if (args.noDisplay)
			return new DummyJoypadInput();
#if SFML_IMPL
		return new Input::SFMLKeyboardJoypadEmulator{
			reinterpret_cast<Graphics::LCDSFML &>(*otherComponents.window),
			std::map<Input::Keys, sf::Keyboard::Key>{
				{Input::RESET,            sf::Keyboard::R},
				{Input::JOYPAD_A,         sf::Keyboard::X},
				{Input::JOYPAD_B,         sf::Keyboard::C},
				{Input::JOYPAD_UP,        sf::Keyboard::Up},
				{Input::JOYPAD_DOWN,      sf::Keyboard::Down},
				{Input::JOYPAD_LEFT,      sf::Keyboard::Left},
				{Input::JOYPAD_RIGHT,     sf::Keyboard::Right},
				{Input::JOYPAD_START,     sf::Keyboard::Return},
				{Input::JOYPAD_SELECT,    sf::Keyboard::BackSpace},
				{Input::ENABLE_DEBUGGING, sf::Keyboard::V}
			}
		};
#elif SDL_IMPL
		return new Input::SDLKeyboardJoypadEmulator(
			reinterpret_cast<Graphics::LCDSDL &>(*otherComponents.window), {
				{Input::RESET,            SDLK_r},
				{Input::JOYPAD_A,         SDLK_x},
				{Input::JOYPAD_B,         SDLK_c},
				{Input::JOYPAD_UP,        SDLK_UP},
				{Input::JOYPAD_DOWN,      SDLK_DOWN},
				{Input::JOYPAD_LEFT,      SDLK_LEFT},
				{Input::JOYPAD_RIGHT,     SDLK_RIGHT},
				{Input::JOYPAD_START,     SDLK_RETURN},
				{Input::JOYPAD_SELECT,    SDLK_BACKSPACE},
				{Input::ENABLE_DEBUGGING, SDLK_v}
			}
		);
#else
		return new DummyJoypadInput();
#endif
	}

	ISound *createISoundImpl(Components &otherComponents, const Args &args)
	{
		if (args.noAudio)
			return new DummySoundPlayer();
#if SFML_IMPL
		return new SFMLSoundPlayer();
#else
		return new DummySoundPlayer();
#endif
	}

	Graphics::ILCD *createILCDImpl(Components &otherComponents, const Args &args)
	{
		if (args.noDisplay)
			return new DummyLCD();
#if SFML_IMPL
		auto win = new Graphics::LCDSFML{sf::VideoMode{640, 576}, "GBEmulator"};

		win->setFramerateLimit(60);
		return win;
#elif SERENITY_IMPL
		Serenity::initSerenityApp();
		return new Graphics::LCDSerenityLibGui{{640, 576}, "GBEmulator"};
#elif SDL_IMPL
		return new Graphics::LCDSDL();
#else
		return new DummyLCD();
#endif
	}

	Network::CableInterface *createCableInterfaceImpl(Components &otherComponents, const Args &args)
	{
#if SFML_IMPL
		auto network = new Network::BGBProtocolCableInterface();

		if (!args.connectIp.empty() && !args.listenPort.empty())
			throw std::invalid_argument("Cannot connect and listen at the same time");
		else if (!args.connectIp.empty())
			network->connect(
				args.connectIp.substr(0, args.connectIp.find(':')),
				std::stoi(args.connectIp.substr(args.connectIp.find(':') + 1))
			);
		else if (!args.listenPort.empty())
			network->host(std::stoi(args.listenPort));
		return network;
#else
		return new DummyCable();
#endif
	}

	Components buildComponents(const Args &args)
	{
		Components components;

		components.network.reset(createCableInterfaceImpl(components, args));
		components.window.reset(createILCDImpl(components, args));
		components.joypad.reset(createJoypadEmulatorImpl(components, args));
		components.sound.reset(createISoundImpl(components, args));
		return components;
	}
}