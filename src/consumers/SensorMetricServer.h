#ifndef AURORA_SENSOR_METRIC_SERVER_H
#define AURORA_SENSOR_METRIC_SERVER_H

#include "eventy/Task.h"
#include "eventy/Metric.h"
#include "eventy/QueueBroker.h"
#include "eventy/Eventy.h"
#include "value/Value.h"

#include "LoRa.h"
#include "SPI.h"
#include "time.h"

namespace aurora {

class SensorMetricServer {
public:
    SensorMetricServer();
    void registerMetrics(eventy::Eventy *eventy_server);
    ~SensorMetricServer();

    double innerTemperature();
    double outerTemperature();
    PositionalData positionalData();
    double altitude();
private:
    eventy::RollingMean *_inner_temperature;
    eventy::RollingMean *_outer_temperature;
    eventy::LatestValue <PositionalData> *_positional_data;
    eventy::RollingMean *_altitude;
};

}

#endif // AURORA_SENSOR_METRIC_SERVER_H
