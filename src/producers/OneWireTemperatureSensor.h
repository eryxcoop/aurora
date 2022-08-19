#ifndef AURORA_ONEWIRE_TEMPERATURE_SENSOR_H
#define AURORA_ONEWIRE_TEMPERATURE_SENSOR_H

#include <DallasTemperature.h>
#include <OneWire.h>

#include "Arduino.h"
#include "eventy/Event.h"
#include "eventy/Task.h"

using namespace eventy;

namespace aurora {

class OneWireTemperatureSensor : public Task {
public:
    OneWireTemperatureSensor(int pin);
    void begin() override;
    EventCollection run() override;
    bool isReady() override;
private:
    OneWire _one_wire;
    DallasTemperature _sensor;
    bool _ready;
    int _pin;
};

}  // namespace aurora

#endif // AURORA_ONEWIRE_TEMPERATURE_SENSOR_H
