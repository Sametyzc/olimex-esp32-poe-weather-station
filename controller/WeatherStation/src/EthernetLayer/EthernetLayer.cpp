#include "EthernetLayer.h"

EthernetLayer::EthernetLayer(String hostname)
{
    Logger::verbose("EthernetLayer::Ethernet()", "Ethernet constructor called");
    ETH.begin();
    ETH.setHostname(hostname.c_str());
    WiFi.onEvent(EthernetEvent);
}

bool EthernetLayer::IsConnected()
{
    return connected_;
}

void EthernetLayer::EthernetEvent(WiFiEvent_t event)
{
  switch (event) {
    case ARDUINO_EVENT_ETH_START:
        Logger::verbose("EthernetLayer::EthernetLayerEvent()", "ETH Started");
        break;
    case ARDUINO_EVENT_ETH_CONNECTED:
        Logger::verbose("EthernetLayer::EthernetLayerEvent()", "ETH Connected");
        break;
    case ARDUINO_EVENT_ETH_GOT_IP:
        connected_ = true;
        break;
    case ARDUINO_EVENT_ETH_DISCONNECTED:
        connected_ = false;
        break;
    case ARDUINO_EVENT_ETH_STOP:
        connected_ = false;
        break;
    default:
        break;
  }
}
