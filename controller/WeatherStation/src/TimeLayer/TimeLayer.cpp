#include "TimeLayer.h"

TimeLayer::TimeLayer(String ntpServer) 
{
    ntpServer_ = ntpServer;
}

TimeLayer::~TimeLayer() 
{

}

unsigned long TimeLayer::GetEpoch()
{
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Logger::warning("TimeLayer::GetEpoch()","Failed to obtain time");
    return 0;
  }
  time(&now);
  return now;
}

void TimeLayer::Initialize()
{
  configTime(0, 0, ntpServer_.c_str());
  Logger::verbose("TimeLayer::Initialize()", "Time initialized");
}

