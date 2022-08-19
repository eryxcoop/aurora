#include "SystemMetricServer.h"

namespace aurora {

SystemMetricServer::SystemMetricServer() {
    _dht_activity = new eventy::PeriodCounter(3);
    _onewire_activity = new eventy::PeriodCounter(3);
    _bmp_activity = new eventy::PeriodCounter(3);
    _accelerometer_activity = new eventy::PeriodCounter(3);
    _gps_data_activity = new eventy::PeriodCounter(3);
    _lora_ok_activity = new eventy::PeriodCounter(3);
    _sd_ok_activity = new eventy::PeriodCounter(3);
}

SystemMetricServer::~SystemMetricServer() {
    delete _dht_activity;
    delete _onewire_activity;
    delete _bmp_activity;
    delete _accelerometer_activity;
    delete _gps_data_activity;
    delete _lora_ok_activity;
    delete _sd_ok_activity;
}

void SystemMetricServer::registerMetrics(eventy::Eventy *eventy_server) {
    eventy_server->registerEventHandler("data/dht/#", _dht_activity);
    eventy_server->registerEventHandler("data/onewire", _onewire_activity);
    eventy_server->registerEventHandler("data/bmp/#", _bmp_activity);
    eventy_server->registerEventHandler("data/accelerometer/#", _accelerometer_activity);
    eventy_server->registerEventHandler("data/gps", _gps_data_activity);
    eventy_server->registerEventHandler("info/lora/ok", _lora_ok_activity);
    eventy_server->registerEventHandler("info/sd/ok", _sd_ok_activity);
}

int SystemMetricServer::freeHEAP() {
    return ESP.getFreeHeap();
}

bool SystemMetricServer::LORAIsActive() {
    int counter = _lora_ok_activity->value(time(NULL) - 10);
    return 0 < counter;
}

bool SystemMetricServer::SDIsActive() {
    int counter = _sd_ok_activity->value(time(NULL) - 23);
    return 0 < counter;
}

bool SystemMetricServer::GPSIsActive() {
    int counter = _gps_data_activity->value(time(NULL) - 10);
    return 0 < counter;
}

bool SystemMetricServer::BMPIsActive() {
    int counter = _bmp_activity->value(time(NULL) - 10);
    return 0 < counter;
}

bool SystemMetricServer::DHTIsActive() {
    int counter = _dht_activity->value(time(NULL) - 10);
    return 0 < counter;
}

bool SystemMetricServer::OneWireIsActive() {
    int counter = _onewire_activity->value(time(NULL) - 10);
    return 0 < counter;
}

bool SystemMetricServer::AccelerometerIsActive() {
    int counter = _accelerometer_activity->value(time(NULL) - 10);
    return 0 < counter;
}

}
