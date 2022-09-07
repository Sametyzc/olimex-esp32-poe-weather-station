#include "SensorLayer.hpp"

SensorLayer::SensorLayer(uint8_t addr,u_int8_t chipid)
{
    Logger::verbose("SensorLayer::SensorLayer()", "SensorLayer constructor called");
    bmp_.begin(addr,chipid);

    bmp_.setSampling(
        Adafruit_BMP280::MODE_NORMAL,  /* Operating Mode. */
        Adafruit_BMP280::SAMPLING_X2,  /* Temp. oversampling */
        Adafruit_BMP280::SAMPLING_X16, /* Pressure oversampling */
        Adafruit_BMP280::FILTER_X16,   /* Filtering. */
        Adafruit_BMP280::STANDBY_MS_500 /* Standby time. */
    );

    tempertureSensor_ = bmp_.getTemperatureSensor();
    pressureSensor_ = bmp_.getPressureSensor();
}

float SensorLayer::GetTemperature()
{
    sensors_event_t event;
    tempertureSensor_->getEvent(&event);
    return event.temperature;
}

float SensorLayer::GetPressure()
{
    sensors_event_t event;
    pressureSensor_->getEvent(&event);
    return event.pressure;
}