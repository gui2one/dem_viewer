#ifndef TIMER_H
#define TIMER_H

#include <pch.h>

class Timer
{
public:
    Timer();

    void update();
    float getDeltaTime();
    float getElapsedTime();

private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    std::chrono::time_point<std::chrono::system_clock> m_now;
    std::chrono::time_point<std::chrono::system_clock> m_now_old;
    int m_elapsed;
    int m_delta;
};

#endif /* TIMER_H */