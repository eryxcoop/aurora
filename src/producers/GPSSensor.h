#ifndef GPS_SENSOR_H
#define GPS_SENSOR_H

#include "eventy/Task.h"
#include "eventy/Event.h"
#include "value/Value.h"

#include "Arduino.h"

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

using namespace eventy;

namespace aurora {

class GPSSensor : public Task {
public:
    GPSSensor(uint8_t rx_pin, uint8_t tx_pin, uint32_t baud);
    ~GPSSensor();
    void begin() override;
    bool isReady() override;
    EventCollection run() override;
private:
    bool _ready;
    bool isValid(double lat, double lng);
    TinyGPSPlus gps;
    SoftwareSerial *_gpsSerial;
    uint8_t _rx_pin, _tx_pin, _baud;
};

}

#endif // GPS_SENSOR_H
