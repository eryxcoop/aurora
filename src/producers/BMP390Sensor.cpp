#include "BMP390Sensor.h"

using namespace eventy;

namespace aurora {

BMP390Sensor::BMP390Sensor(double sea_level_pressure) : _sea_level_pressure(sea_level_pressure) {

}

// TODO: modificar para que sea seguro de llamar multiples veces
void BMP390Sensor::begin() {
    if (!_bmp.begin_I2C()) {
        Serial.println("Could not find a valid BMP390 sensor, check wiring!");
        _ready = false;
    } else {
        Serial.println("AuroraBMP390 begin!");
        // Set up oversampling and filter initialization
        _bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
        _bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
        _bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
        _bmp.setOutputDataRate(BMP3_ODR_50_HZ);
        _ready = true;
    }
}

bool BMP390Sensor::isReady() {
    return _ready;
}

EventCollection BMP390Sensor::run() {
    EventCollection events;
    if (!_bmp.performReading())
        return events;

    events.push(EventFactory::create("data/bmp/temperature", _bmp.temperature));

    events.push(EventFactory::create("data/bmp/pressure", _bmp.pressure / 100.0));

    events.push(EventFactory::create("data/bmp/altitude", _bmp.readAltitude(_sea_level_pressure)));
    return events;
}

}
