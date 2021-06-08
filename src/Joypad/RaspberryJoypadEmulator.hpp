/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** RaspberryJoypadEmulator.hpp
*/
#ifndef GBEMULATOR_RASPBERRYJOYPADEMULATOR_HPP
#define GBEMULATOR_RASPBERRYJOYPADEMULATOR_HPP

#include <map>
#include <thread>
#include "JoypadEmulator.hpp"

namespace GBEmulator::Input
{
	class RaspberryJoypadEmulator : public JoypadEmulator {
	private:
		standard::map<Keys, uint8_t> _keys;

	public:
		RaspberryJoypadEmulator() = delete;
		RaspberryJoypadEmulator(const RaspberryJoypadEmulator &) = delete;
		~RaspberryJoypadEmulator() = default;
		RaspberryJoypadEmulator &operator=(const RaspberryJoypadEmulator &) = delete;
		explicit RaspberryJoypadEmulator(const standard::map<Keys, uint8_t> &&keys);
		void update();
		bool isButtonPressed(Keys button) const noexcept override;
	};
}


#endif //GBEMULATOR_RASPBERRYJOYPADEMULATOR_HPP
