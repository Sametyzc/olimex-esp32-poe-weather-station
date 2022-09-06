
#ifndef TIME_LAYER_H
#define TIME_LAYER_H

#include <Arduino.h>
#include <Logger.h>

class TimeLayer 
{
    public:
        TimeLayer(String ntpServer);
        ~TimeLayer();
        unsigned long GetEpoch();
        void Initialize();
    private:
        String ntpServer_;
};

#endif