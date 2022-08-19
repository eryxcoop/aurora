#ifndef AURORA_SYSTEM_METRICS_SERVER_H
#define AURORA_SYSTEM_METRICS_SERVER_H

#include "Arduino.h"
#include "eventy/Task.h"
#include "eventy/EventHandler.h"
#include "eventy/QueueBroker.h"
#include "eventy/Metric.h"
#include "eventy/Eventy.h"

#include "time.h"

namespace aurora {

class SystemMetricServer {
public:
    SystemMetricServer();
    ~SystemMetricServer();
    void registerMetrics(eventy::Eventy *eventy_server);

    int freeHEAP();
    int mainQueueEventsAwaiting();
    bool LORAIsActive();
    bool SDIsActive();
    bool GPSIsActive();
    bool BMPIsActive();
    bool DHTIsActive();
    bool OneWireIsActive();
    bool AccelerometerIsActive();
private:
    eventy::PeriodCounter *_dht_activity;
    eventy::PeriodCounter *_onewire_activity;
    eventy::PeriodCounter *_bmp_activity;
    eventy::PeriodCounter *_accelerometer_activity;
    eventy::PeriodCounter *_gps_data_activity;
    eventy::PeriodCounter *_lora_ok_activity;
    eventy::PeriodCounter *_sd_ok_activity;
};

}

#endif  // AURORA_SYSTEM_METRICS_SERVER_H
