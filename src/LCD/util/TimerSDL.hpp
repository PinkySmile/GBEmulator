/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** TimerSDL.hpp
*/
#ifndef GBEMULATOR_TIMERSDL_HPP
#define GBEMULATOR_TIMERSDL_HPP


class TimerSDL {
	private:
		int startTicks;
		bool started;

	public:
		TimerSDL();
		void reset();
		void start();
		void stop();
		int get_ticks();
};

#endif //GBEMULATOR_TIMERSDL_HPP
