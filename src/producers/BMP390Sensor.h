#ifndef BMP390SENSOR_H
#define BMP390SENSOR_H

#include "eventy/Task.h"
#include "eventy/Event.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_BMP3XX.h"

using namespace eventy;

namespace aurora {

class BMP390Sensor : public Task {
public:
    BMP390Sensor(double sea_level_pressure);
    void begin() override;
    bool isReady() override;
    EventCollection run() override;
private:
    bool _ready;
    Adafruit_BMP3XX _bmp;
    double _sea_level_pressure;
};

}

#endif // BMP390SENSOR_H
