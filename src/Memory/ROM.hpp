/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Rom.hpp
*/

#ifndef GBEMULATOR_ROM_HPP
#define GBEMULATOR_ROM_HPP


#include <string>
#include "Memory.hpp"

namespace GBEmulator
{
	class InvalidRomException : public std::exception {
	private:
		std::string _msg;

	public:
		InvalidRomException(const std::string &msg) : _msg(msg) {};
		const char *what() const noexcept override { return this->_msg.c_str(); };
	};

	class ROM : public Memory {
	public:
		ROM(const std::string &path, unsigned short bankSize);
	};
}


#endif //GBEMULATOR_ROM_HPP
