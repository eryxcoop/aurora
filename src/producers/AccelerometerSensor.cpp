#include "AccelerometerSensor.h"

#include "Arduino.h"

using namespace eventy;

namespace aurora {

AccelerometerSensor::AccelerometerSensor(int x_pin, int y_pin, int z_pin, int adc_resolution, double adc_max_voltage) {
    this->x_pin = x_pin;
    this->y_pin = y_pin;
    this->z_pin = z_pin;
    this->adc_resolution = adc_resolution;
    this->adc_max_voltage = adc_max_voltage;
    _ready = true;
}

bool AccelerometerSensor::isReady() {
    return _ready;
}

EventCollection AccelerometerSensor::run() {
    EventCollection events;
    int x_adc_value, y_adc_value, z_adc_value;

    x_adc_value = analogRead(x_pin);
    events.push(EventFactory::create("data/accelerometer/x", x_adc_value));

    y_adc_value = analogRead(y_pin);
    events.push(EventFactory::create("data/accelerometer/y", y_adc_value));

    z_adc_value = analogRead(z_pin);
    events.push(EventFactory::create("data/accelerometer/z", z_adc_value));

    return events;
}

/* double AccelerometerSensor::voltageToMetersPerSecond(uint adc_sensed_voltage, double calibration) const { */
/*     // https://www.researchgate.net/post/conversion_of_ADXL_335_raw_data_into_g */

/*     double sensed_voltage = (adc_sensed_voltage * adc_max_voltage) / adc_resolution; */
/*     double bias = adc_max_voltage / 2; */
/*     double acceleration_in_g = ((sensed_voltage - bias + calibration) / SENSITIVITY); */
/*     return acceleration_in_g * G_ACCELERATION; */
/* } */

/* String AccelerometerSensor::measurementToString(const AccelerometerMeasurement* measurement) const { */
/*     String measurement_string = ""; */
/*     measurement_string += "X: " + String(measurement->x) + ", "; */
/*     measurement_string += "Y: " + String(measurement->y) + ", "; */
/*     measurement_string += "Z: " + String(measurement->z) + ", "; */

/*     double x_in_ms2, y_in_ms2, z_in_ms2; */
/*     x_in_ms2 = voltageToMetersPerSecond(measurement->x, X_AXIS_CALIBRATION); */
/*     y_in_ms2 = voltageToMetersPerSecond(measurement->y, Y_AXIS_CALIBRATION); */
/*     z_in_ms2 = voltageToMetersPerSecond(measurement->z, Z_AXIS_CALIBRATION); */

/*     measurement_string += "X in m/s^2: " + String(x_in_ms2) + ", "; */
/*     measurement_string += "Y in m/s^2: " + String(y_in_ms2) + ", "; */
/*     measurement_string += "Z in m/s^2: " + String(z_in_ms2); */
/*     return measurement_string; */
/* } */

}  // namespace aurora
