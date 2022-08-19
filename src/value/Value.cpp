#include "Value.h"

EVENT_TYPE_REGISTER(aurora::PositionalData, EVENT_TYPE_GPS)

namespace aurora {

// PositionalData 
PositionalData::PositionalData() {
}

PositionalData::PositionalData(uint8_t hour, uint8_t minute, uint8_t second, double latitude, double longitude,
                               double altitude) :
    _hour(hour),
    _minute(minute),
    _second(second),
    _latitude(latitude),
    _longitude(longitude),
    _altitude(altitude) {

}

uint8_t PositionalData::hour() const {
    return _hour;
}

uint8_t PositionalData::minute() const {
    return _minute;
}

uint8_t PositionalData::second() const {
    return _second;
}

double PositionalData::longitude() const {
    return _longitude;
}

double PositionalData::latitude() const {
    return _latitude;
}

double PositionalData::altitude() const {
    return _altitude;
}

}
