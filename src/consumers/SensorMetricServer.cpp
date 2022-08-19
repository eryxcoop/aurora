#include "SensorMetricServer.h"

namespace aurora {

SensorMetricServer::SensorMetricServer() {
    _inner_temperature = new eventy::RollingMean(6);
    _outer_temperature = new eventy::RollingMean(6);
    _positional_data = new eventy::LatestValue<PositionalData>();
    _altitude = new eventy::RollingMean(6);
}

SensorMetricServer::~SensorMetricServer() {
    delete _inner_temperature;
    delete _outer_temperature;
    delete _positional_data;
    delete _altitude;
}

void SensorMetricServer::registerMetrics(eventy::Eventy *eventy_server) {
    eventy_server->registerEventHandler("data/dht/temperature", _inner_temperature);
    eventy_server->registerEventHandler("data/bmp/temperature", _outer_temperature);
    eventy_server->registerEventHandler("data/gps", _positional_data);
    eventy_server->registerEventHandler("data/bmp/altitude", _altitude);
}

double SensorMetricServer::innerTemperature() {
    return _inner_temperature->value(time(NULL) - 10);
}

double SensorMetricServer::outerTemperature() {
    return _outer_temperature->value(time(NULL) - 10);
}

PositionalData SensorMetricServer::positionalData() {
    return _positional_data->value();
}

double SensorMetricServer::altitude() {
    return _altitude->value(time(NULL) - 10);
}

}
