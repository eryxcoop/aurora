#include "StatusIndicator.h"

using namespace eventy;

namespace aurora {

StatusIndicator::StatusIndicator(SystemMetricServer *metric_server, int leds_pin, int leds_count) :
    _metric_server(metric_server),
    _leds_pin(leds_pin),
    _leds_count(leds_count) {

}

void StatusIndicator::begin() {
    if (_leds != nullptr)
        delete _leds;

    pinMode(_leds_pin, OUTPUT);
    _leds = new Adafruit_NeoPixel(_leds_count, _leds_pin, NEO_GRB + NEO_KHZ800);
    _leds->begin();
    _leds->setBrightness(10);

    initialization_begin();
    _ready = true;
}

StatusIndicator::~StatusIndicator() {
    if (_leds != nullptr)
        delete _leds;
}

bool StatusIndicator::isReady() {
    return _ready;
}

EventCollection StatusIndicator::run() {
    EventCollection events;

    setLedStatus(0, _metric_server->LORAIsActive());
    setLedStatus(1, _metric_server->SDIsActive());

    setLedStatus(3, _metric_server->GPSIsActive());
    setLedStatus(4, _metric_server->BMPIsActive());
    setLedStatus(5, _metric_server->DHTIsActive());
    setLedStatus(6, _metric_server->OneWireIsActive());
    setLedStatus(7, _metric_server->AccelerometerIsActive());

    _leds->show();

    return events;
}

void StatusIndicator::setLedStatus(int position, bool status) {
    _leds->setPixelColor(position, status ? green_color() : red_color());
}

void StatusIndicator::initialization_begin() {
    for (size_t i = 0; i < _leds_count; i++) {
        _leds->setPixelColor(i, no_color());
    }
    _leds->show();
    delay(200);
    for (size_t i = 0; i < _leds_count; i++) {
        _leds->setPixelColor(i, white_color());
        _leds->show();
        delay(100);
    }
    for (size_t i = 0; i < _leds_count; i++) {
        _leds->setPixelColor(i, no_color());
    }
    _leds->show();
    delay(200);
    for (size_t i = 0; i < _leds_count; i++) {
        _leds->setPixelColor(i, white_color());
        _leds->show();
        delay(100);
    }
}

uint32_t StatusIndicator::red_color() { return _leds->Color(255, 0, 0); }

uint32_t StatusIndicator::green_color() { return _leds->Color(0, 255, 0); }

uint32_t StatusIndicator::white_color() { return _leds->Color(255, 255, 255); }

uint32_t StatusIndicator::no_color() { return _leds->Color(0, 0, 0); }

}
