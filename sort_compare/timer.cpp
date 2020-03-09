#include <iostream>
#include <chrono>
#include "timer.hpp"

//using clock_t = std::chrono::steady_clock;
using namespace std::chrono;
Timer::Timer() : m_begin(std::chrono::steady_clock::now()), duration(0), is_work(true) {}

Timer::~Timer() {
	if (is_work)
        	this->stop();
        std::cout << duration << " milliseconds" << std::endl;
}

void Timer::stop() {
        auto end = std::chrono::steady_clock::now();
        duration += std::chrono::duration_cast<std::chrono::milliseconds> (end - m_begin).count();
	is_work = false;
}

void Timer::go() {
        m_begin = std::chrono::steady_clock::now();
	is_work = true;
}
