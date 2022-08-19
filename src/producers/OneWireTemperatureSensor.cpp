#include "OneWireTemperatureSensor.h"

#include "Arduino.h"

using namespace eventy;


namespace aurora {

OneWireTemperatureSensor::OneWireTemperatureSensor(int pin) : _pin(pin) {

}

// TODO: modificar para que sea seguro de llamar multiples veces
void OneWireTemperatureSensor::begin() {
    _one_wire.begin(_pin);
    _sensor.setOneWire(&_one_wire);
    _ready = true; // TODO:
}

bool OneWireTemperatureSensor::isReady() {
    return _ready;
}

EventCollection OneWireTemperatureSensor::run() {
    EventCollection events;
    double _temperature;
    _sensor.requestTemperaturesByIndex(0);
    _temperature = _sensor.getTempCByIndex(0);

    events.push(EventFactory::create("data/onewire", _temperature));
    return events;
}

}  // namespace aurora
