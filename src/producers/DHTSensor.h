#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include "eventy/Event.h"
#include "eventy/Task.h"

#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include "DHT.h"

using namespace eventy;

namespace aurora {

class DHTSensor : public Task {
public:
    ~DHTSensor();
    DHTSensor(uint8_t pin, uint8_t type);
    void begin() override;
    EventCollection run() override;
    bool isReady() override;
private:
    DHT *_dht = nullptr;
    bool _ready;
    uint8_t _pin, _type;
};

}

#endif // DHT_SENSOR_H
