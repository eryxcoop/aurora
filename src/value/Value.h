#ifndef AURORA_VALUE_H
#define AURORA_VALUE_H

#include "Arduino.h"
#include "eventy/Event.h"

#define EVENT_TYPE_GPS 100

namespace aurora {

class PositionalData {
public:
    PositionalData();
    PositionalData(uint8_t hour, uint8_t minute, uint8_t second, double latitude, double longitude, double altitude);
    uint8_t hour() const;
    uint8_t minute() const;
    uint8_t second() const;
    double longitude() const;
    double latitude() const;
    double altitude() const;
private:
    uint8_t _hour = 0;
    uint8_t _minute = 0;
    uint8_t _second = 0;
    double _longitude = 0;
    double _latitude = 0;
    double _altitude = 0;
};

}

#endif // AURORA_VALUE_H
