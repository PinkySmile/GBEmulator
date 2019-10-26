/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Timer.hpp
*/

#ifndef GBEMULATOR_TIMER_HPP
#define GBEMULATOR_TIMER_HPP


#define GB_CPU_FREQUENCY 4194304

namespace GBEmulator::Timing
{
	double getCyclesPerSecondsFromFrequency(unsigned char frequency);

	class Timer {
	private:
		double _expected;
		double _cycles = 0;
		unsigned char _byte = 0;
		unsigned char _counter = 0;

	public:
		Timer();
		~Timer() = default;
		Timer(const Timer &) = delete;
		Timer &operator=(const Timer &) = delete;
		unsigned char modulo = 0;

		bool isActivated() const;
		unsigned getFrequency() const;
		unsigned char getControlByte() const;
		unsigned char getCounter() const;

		void setCounter(unsigned char byte);
		void setControlByte(unsigned char byte);
		bool update(unsigned cycles);
	};
}


#endif //GBEMULATOR_TIMER_HPP
