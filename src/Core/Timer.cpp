#include "Timer.h"

Timer::Timer()
{
    m_start = std::chrono::system_clock::now();
    m_elapsed = 0;
    m_delta = 0;
    m_now = m_start;
    m_now_old = m_start;
}

void Timer::update()
{

    m_now = std::chrono::system_clock::now();
    auto delay = std::chrono::duration_cast<std::chrono::milliseconds>(m_now - m_start);
    m_elapsed = delay.count(); // holy graal !!!

    auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(m_now - m_now_old);
    m_delta = delta.count();
    m_now_old = m_now;
}

float Timer::getDeltaTime()
{

    return (float)m_delta / 1000.0;
}

float Timer::getElapsedTime()
{
    return (float)m_elapsed / 1000.0;
}
