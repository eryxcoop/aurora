#ifndef AURORA_STATUS_INDICATOR
#define AURORA_STATUS_INDICATOR

#include "eventy/Task.h"
#include "consumers/SystemMetricServer.h"

#include "Adafruit_NeoPixel.h"

using namespace eventy;

namespace aurora {

class StatusIndicator : public Task {
public:
    StatusIndicator(SystemMetricServer *metric_server, int leds_pin, int leds_count);
    ~StatusIndicator();
    EventCollection run() override;
    bool isReady() override;
    void begin() override;
    void initialization_begin();
private:
    bool _ready;
    int _leds_pin;
    int _leds_count;
    Adafruit_NeoPixel *_leds = nullptr;
    SystemMetricServer *_metric_server;

    void setLedStatus(int position, bool status);
    uint32_t red_color();
    uint32_t green_color();
    uint32_t white_color();
    uint32_t no_color();

};

}

#endif //  AURORA_STATUS_INDICATOR
