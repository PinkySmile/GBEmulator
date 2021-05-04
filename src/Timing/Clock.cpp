//
// Created by andgel on 03/05/2021
//

#include <cstdio>
#include "Clock.hpp"

namespace GBEmulator::Timing
{
#ifdef __serenity__
	Clock::Clock() :
		_start(this->_getTime())
	{
	}

	Time Clock::getElapsedTime() const
	{
		return this->_getTime() - this->_start;
	}

	Time Clock::restart()
	{
		auto time = this->_getTime();
		auto result = time - this->_start;

		this->_start = time;
		return result;
	}

	Time Clock::_getTime() const
	{
		timespec time;

		clock_gettime(CLOCK_MONOTONIC, &time);
		return Time{static_cast<uint64_t>(time.tv_sec) * 1000000 + time.tv_nsec / 1000};
	}

	Time::Time(uint64_t time) :
		_micro(time)
	{
	}

	float Time::asSeconds() const
	{
		return this->_micro / 1000000.f;
	}

	uint32_t Time::asMilliseconds() const
	{
		return this->_micro / 1000;
	}

	uint64_t Time::asMicroSeconds() const
	{
		return this->_micro;
	}

	Time Time::operator-(const Time &other) const
	{
		return Time(this->_micro - other._micro);
	}

	Time Time::operator+(const Time &other) const
	{
		return Time(this->_micro + other._micro);
	}

	Time &Time::operator-=(const Time &other)
	{
		this->_micro -= other._micro;
		return *this;
	}

	Time &Time::operator+=(const Time &other)
	{
		this->_micro += other._micro;
		return *this;
	}
#endif
}