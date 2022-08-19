#ifndef ACCELEROMETER_SENSOR_H
#define ACCELEROMETER_SENSOR_H

#include "Arduino.h"
#include "eventy/Event.h"
#include "eventy/Task.h"

#define SENSITIVITY 0.3  // 330mV/g
#define X_AXIS_CALIBRATION 0.2
#define Y_AXIS_CALIBRATION 0.2
#define Z_AXIS_CALIBRATION 0.2
#define G_ACCELERATION 9.80665

using namespace eventy;

namespace aurora {

class AccelerometerSensor : public Task {
public:
    AccelerometerSensor(int x_pin, int y_pin, int z_pin, int adc_resolution, double adc_max_voltage);
    bool isReady() override;
    EventCollection run() override;
private:
    bool _ready;
    int x_pin, y_pin, z_pin, adc_resolution;
    double adc_max_voltage;
    double voltageToMetersPerSecond(uint adc_sensed_voltage, double calibration) const;
};

}  // namespace aurora

#endif // ACCELEROMETER_SENSOR_H
