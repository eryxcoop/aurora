#include "Buzzer.h"

using namespace eventy;

namespace aurora {

Buzzer::Buzzer(uint8_t pin) : _pin(pin) {

}

void Buzzer::begin() {
    Serial.println("Buzzer begin!");
    pinMode(_pin, OUTPUT);
    _ready = true; // TODO:
}

bool Buzzer::isReady() {
    return _ready;
}

EventCollection Buzzer::run() {
    EventCollection events;

    digitalWrite(_pin, HIGH);
    delay(100);
    digitalWrite(_pin, LOW);
    delay(75);
    digitalWrite(_pin, HIGH);
    delay(100);
    digitalWrite(_pin, LOW);

    return events;
}

} 
