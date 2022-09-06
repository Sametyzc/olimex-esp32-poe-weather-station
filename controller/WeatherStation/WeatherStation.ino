#include "src/EthernetLayer/EthernetLayer.h"
#include "src/TimeLayer/TimeLayer.h"
#include "src/SmartDelay/SmartDelay.h"
#include "src/ClientLayer/ClientLayer.h"
#include "src/MemorySegment/MemorySegment.h"

#include <Logger.h>

const unsigned short int  stationIndex = 0;

const String ntpServer("pool.ntp.org");
const unsigned long delayTime = 300000; // 5 minutes

const String hostname("192.168.0.137");
const unsigned short int port = 8000;

struct WeatherData
{
    unsigned short int stationIndex;
    unsigned long timestamp;
    float temperature;
    float pressure;
};

SmartDelay _smartDelay(delayTime);
MemorySegment<WeatherData> _memorySegment(5,500);

// Layer objects
EthernetLayer _ethernet("esp32-weather-station-"+String(stationIndex));
TimeLayer _time(ntpServer);
ClientLayer _client(hostname,port,new UrlEncoded());

void setup() 
{
  Serial.begin(115200);
  while (!Serial) {
    Logger::verbose("setup()", "Waiting for serial port to be ready!");
    delay(1000);
  }
  Logger::verbose("setup()", "Serial port connected");

  while (!_ethernet.IsConnected()) {
    Logger::verbose("setup()", "Waiting for ethernet connection");
    delay(1000);
  }

  // Should be called after ethernet connection
  _time.Initialize();

}

void loop() 
{
  _smartDelay.StartTimer(_time.GetEpoch());

  Variable stationIndexVar{ .name = "STATION",.value = String(stationIndex)};
  Variable epochVar{ .name = "EPOCH",.value = String(_time.GetEpoch())};
  // Variable tempertureVar{ .name = "TEMP",.value = String(_time.GetEpoch())};
  // Variable pressureVar{ .name = "BARO",.value = String(_time.GetEpoch())};

  if(_ethernet.IsConnected())
  {
    _client.contentType->variableList.add(stationIndexVar);
    _client.contentType->variableList.add(epochVar);
    // _client.contentType->variableList.add(tempertureVar);
    // _client.contentType->variableList.add(pressureVar);

    String response = _client.Post("/SenserData");
    Serial.println("-----------Response-----------");
    Serial.println(response);
    Serial.println("------------------------------");
  }
  else
  {
    Logger::verbose("loop()", "Ethernet not connected");
    // _memorySegment.Add(new WeatherData{stationIndex,_time.GetEpoch(),tempertureVar.value.toFloat(),pressureVar.value.toFloat()});
  }

  _smartDelay.EndTimer(_time.GetEpoch());
  delay(_smartDelay.GetDelay());
  _smartDelay.ResetTimer();
}