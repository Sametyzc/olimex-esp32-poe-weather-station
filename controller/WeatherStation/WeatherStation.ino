#include "src/EthernetLayer/EthernetLayer.hpp"
#include "src/TimeLayer/TimeLayer.hpp"
#include "src/SmartDelay/SmartDelay.hpp"
#include "src/ClientLayer/ClientLayer.hpp"
#include "src/MemorySegment/MemorySegment.hpp"
#include "src/SensorLayer/SensorLayer.hpp"

#include <Logger.h>

const unsigned short int  stationIndex = 0;

const String ntpServer("pool.ntp.org");
const unsigned long delayTime = 300000; // 5 minutes

const String hostname("192.168.0.137");
const unsigned short int port = 8000;

const unsigned char bmpSensorAddress = 0x76;

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
SensorLayer _sensor(bmpSensorAddress);

void SendWeatherData(WeatherData* weatherData)
{
    Variable stationIndexVariable{ .name = "stationIndex",.value = String(weatherData->stationIndex)};
    Variable timestampVariable{ .name = "timestamp",.value = String(weatherData->timestamp)};
    Variable temperatureVariable{ .name = "temperature",.value = String(weatherData->temperature)};
    Variable pressureVariable{ .name = "pressure",.value = String(weatherData->pressure)};

    _client.contentType->variableList.add(stationIndexVariable);
    _client.contentType->variableList.add(timestampVariable);
    _client.contentType->variableList.add(temperatureVariable);
    _client.contentType->variableList.add(pressureVariable);

    String response = _client.Post("/SenserData");
    Serial.println("-----------Response-----------");
    Serial.println(response);
    Serial.println("------------------------------");
}

void setup() 
{
  Logger::setLogLevel(Logger::VERBOSE);

  Serial.begin(115200);
  while (!Serial) {
    delay(50);
  }

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

  WeatherData* weatherData = new WeatherData
  {
    .stationIndex = stationIndex,
    .timestamp = _time.GetEpoch(),
    .temperature = _sensor.GetTemperature(),
    .pressure = _sensor.GetPressure()
  };

  if(_ethernet.IsConnected())
  {
    if(_memorySegment.HasValue())
    {
      for(int i = 0; i < _memorySegment.GetSegmentCount(); i++)
      {
        MsVectorData<WeatherData>* msVectorData = _memorySegment.GetSegment(i);
        for(int j = 0; j < msVectorData->size(); j++)
        {
          SendWeatherData(msVectorData->at(j));
        }
      }
      _memorySegment.ClearAll();
    }
    SendWeatherData(weatherData);
    delete weatherData;
  }
  else
  {
    Logger::verbose("loop()", "Ethernet not connected");
    _memorySegment.Add(weatherData);
  }

  _smartDelay.EndTimer(_time.GetEpoch());
  delay(_smartDelay.GetDelay());
  _smartDelay.ResetTimer();
}