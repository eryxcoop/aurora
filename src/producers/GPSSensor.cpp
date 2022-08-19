#include "GPSSensor.h"

using namespace eventy;

namespace aurora {

GPSSensor::GPSSensor(uint8_t rx_pin, uint8_t tx_pin, uint32_t baud) : _rx_pin(rx_pin), _tx_pin(tx_pin), _baud(baud) {

}

void GPSSensor::begin() {
    if (_gpsSerial != nullptr)
        delete _gpsSerial;
    Serial.println("AuroraGPS begin!");
    _gpsSerial = new SoftwareSerial(_rx_pin, _tx_pin);
    _gpsSerial->begin(_baud);
    _ready = true;
}

GPSSensor::~GPSSensor() {
    if (_gpsSerial != nullptr)
        delete _gpsSerial;
}
bool GPSSensor::isReady() {
    return _ready;
}

EventCollection GPSSensor::run() {
    EventCollection events;

    while (_gpsSerial->available() > 0) {
        if (gps.encode(_gpsSerial->read())) {
            if (gps.location.isValid()) {
                uint8_t hour = gps.time.hour();
                uint8_t minute = gps.time.minute();
                uint8_t second = gps.time.second();
                double lat = gps.location.lat();
                double lng = gps.location.lng();
                double altitude = gps.altitude.meters();
                if (isValid(lat, lng)) {
                    PositionalData positional_data(hour, minute, second, lat, lng, altitude);
                    events.push(EventFactory::create("data/gps", positional_data));
                    delay(500);
                    return events;
                }
            }
        }
    }

    return events;
}

bool GPSSensor::isValid(double lat, double lng) {
    return -60 <= lat && lat <= -10 && -90 <= lng && lng <= -30;
}

} 
