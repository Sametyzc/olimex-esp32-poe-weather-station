
#ifndef SMART_DELAY_H
#define SMART_DELAY_H

#include <Arduino.h>
#include <ETH.h>
#include <Logger.h>

class SmartDelay
{
    public:
        SmartDelay(unsigned long delay);
        ~SmartDelay();
        void StartTimer(unsigned long time);
        void EndTimer(unsigned long time);
        unsigned long GetDelay();
        void ResetTimer();

    private:
        unsigned long delay_;
        unsigned long startTime_;
        unsigned long endTime_;
};

#endif