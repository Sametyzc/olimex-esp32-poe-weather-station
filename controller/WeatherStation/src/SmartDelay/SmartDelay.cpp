#include "SmartDelay.hpp"

SmartDelay::SmartDelay(unsigned long delay)
{
    delay_ = delay;
    startTime_ = 0;
    endTime_ = 0;
}

SmartDelay::~SmartDelay()
{

}

void SmartDelay::StartTimer(unsigned long time)
{
    startTime_ = time;
}

void SmartDelay::EndTimer(unsigned long time)
{
    endTime_ = time;
}

unsigned long SmartDelay::GetDelay()
{
    unsigned long timeElapsed = endTime_ - startTime_;
    if (timeElapsed < delay_)
    {
        return delay_ - timeElapsed;
    }
    else
    {
        return delay_;
    }
}

void SmartDelay::ResetTimer()
{
    startTime_ = 0;
    endTime_ = 0;
}