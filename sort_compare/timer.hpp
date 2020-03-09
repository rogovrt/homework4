#ifndef TIMER_H
#define ANIMAL_H

//public:
//using clock_t = std::chrono::steady_clock;
//using timepoint_t = clock_t::time_point;
//using namespace std::chrono;
class Timer {
public:
    Timer();

    ~Timer();

    void stop();

    void go();

private:
    std::chrono::steady_clock::time_point m_begin;
    int duration;
    bool is_work;
};

#endif
