#include "DHTSensor.h"

using namespace eventy;

namespace aurora {

DHTSensor::DHTSensor(uint8_t pin, uint8_t type) : _pin(pin), _type(type) {

}

void DHTSensor::begin() {
    if (_dht != nullptr)
        delete _dht;
    Serial.println("AuroraDHt begin!");
    _dht = new DHT(_pin, _type);
    _dht->begin();
    _ready = true; // TODO:
}

DHTSensor::~DHTSensor() {
    if (_dht != nullptr)
        delete _dht;
}

bool DHTSensor::isReady() {
    return _ready;
}

EventCollection DHTSensor::run() {
    EventCollection events;

    double _temperature = _dht->readTemperature(false, true);
    if (!isnan(_temperature)) {
        events.push(EventFactory::create("data/dht/temperature", _temperature));
    }

    double _humidity = _dht->readHumidity(true);
    if (!isnan(_humidity)) {
        events.push(EventFactory::create("data/dht/humidity", _humidity));
    }
    return events;
}

} 
