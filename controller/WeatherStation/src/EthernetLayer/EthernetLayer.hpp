
#ifndef ETHERNET_LAYER_H
#define ETHERNET_LAYER_H

#include <Arduino.h>
#include <ETH.h>
#include <Logger.h>

class EthernetLayer
{
    public:
        EthernetLayer(String hostname);
        bool IsConnected();

    private:
        inline static bool connected_ = false;
        static void EthernetEvent(WiFiEvent_t);
};

#endif