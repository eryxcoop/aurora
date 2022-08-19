#ifndef BUZZER_H
#define BUZZER_H

#include "eventy/Event.h"
#include "eventy/Task.h"

#include "Arduino.h"

using namespace eventy;

namespace aurora {

class Buzzer : public Task {
public:
    Buzzer(uint8_t pin);
    void begin() override;
    EventCollection run() override;
private:
    bool isReady() override;
    bool _ready = false;
    int _pin;
};

}

#endif // BUZZER_H
