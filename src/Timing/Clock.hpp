//
// Created by andgel on 03/05/2021
//

#ifndef GBEMULATOR_CLOCK_HPP
#define GBEMULATOR_CLOCK_HPP


#if SFML_IMPL
#include <SFML/System.hpp>
#else
#include <ctime>
#include <cstdint>
#endif

namespace GBEmulator::Timing
{
#if !SFML_IMPL
	struct Time {
	private:
		uint64_t _micro;

	public:
		Time() = delete;
		Time(uint64_t time);
		float asSeconds() const;
		uint32_t asMilliseconds() const;
		uint64_t asMicroSeconds() const;
		Time operator-(const Time &other) const;
		Time operator+(const Time &other) const;
		Time &operator-=(const Time &other);
		Time &operator+=(const Time &other);
	};

	class Clock {
	private:
		Time _start;

		Time _getTime() const;
	public:
		Clock();
		Time getElapsedTime() const;
		Time restart();
	};
#else
	using Clock = sf::Clock;
#endif
}


#endif //GBEMULATOR_CLOCK_HPP
