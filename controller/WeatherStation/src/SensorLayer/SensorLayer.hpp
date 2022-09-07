
#ifndef SENSOR_LAYER_H
#define SENSOR_LAYER_H

#include <Logger.h>
#include <Adafruit_BMP280.h>

class SensorLayer
{
    public:
        SensorLayer(uint8_t addr=(uint8_t)119U,u_int8_t chipid=(uint8_t)88U);
        float GetTemperature();
        float GetPressure();
        
    private:
        Adafruit_BMP280 bmp_;
        Adafruit_Sensor* tempertureSensor_;
        Adafruit_Sensor* pressureSensor_;
};

#endif