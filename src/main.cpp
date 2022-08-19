#include "Arduino.h"
#include "Eventy.h"
#include "esp_wifi.h"
#include "time.h"

// Producers
#include "producers/DHTSensor.h"
#include "producers/BMP390Sensor.h"
#include "producers/OneWireTemperatureSensor.h"
#include "producers/AccelerometerSensor.h"
#include "producers/GPSSensor.h"

// Consumers
#include "consumers/SensorMetricServer.h"
#include "consumers/SystemMetricServer.h"

// Services
#include "services/SerialPrinter.h"
#include "services/SDWriter.h"
#include "services/LoRaTransmitter.h"
#include "services/StatusIndicator.h"
#include "services/Buzzer.h"
#include "Configuration.h"

using namespace aurora;

eventy::Eventy eventy_manager;

// Producers
DHTSensor DHT_sensor(DHT_PIN, DHT22);
BMP390Sensor BMP_sensor(SEA_LEVEL_PRESSURE_HPA);
OneWireTemperatureSensor OneWire_sensor(ONE_WIRE_PIN);
AccelerometerSensor ACC_sensor(ACCELEROMETER_X_PIN, ACCELEROMETER_Y_PIN, ACCELEROMETER_Z_PIN, ADC_SCALE,
                               ADC_MAX_VOLTAGE);
GPSSensor GPS_sensor(GPS_RX_PIN, GPS_TX_PIN, GPS_BAUD);

// Consumers
SystemMetricServer system_metric_server;
SensorMetricServer sensor_metric_server;

// Services
SerialPrinter serial_printer;
SDWriter sd_writer;
LoRaTransmitter lora(&sensor_metric_server, LORA_CS_PIN, LORA_RESET_PIN, LORA_IRQ_PIN, LORA_SCK_PIN, LORA_MISO_PIN,
                     LORA_MOSI_PIN, LORA_FREQUENCY_IN_MHZ);
Buzzer buzzer(BUZZER_PIN);
StatusIndicator status_indicator(&system_metric_server, STATE_INDICATOR_LEDS_PIN, INICATOR_LEDS_COUNT);


void setup() {
    Serial.begin(115200);

    esp_wifi_stop();
    btStop();

    delay(10);

    // Register event handlers
    serial_printer.begin(115200);
    eventy_manager.registerEventHandler("data/#", &serial_printer);
    sd_writer.begin(SD_CS_PIN);
    eventy_manager.registerEventHandler("data/#", &sd_writer);
    system_metric_server.registerMetrics(&eventy_manager);
    sensor_metric_server.registerMetrics(&eventy_manager);

    // Registers tasks
    eventy_manager.registerTask(&DHT_sensor, DHT_INTERVAL, "DHT_sensor", 2048, CORE_1);
    eventy_manager.registerTask(&BMP_sensor, BMP_INTERVAL, "BMP_sensor", 2048, CORE_1);
    eventy_manager.registerTask(&OneWire_sensor, ONEWIRE_INTERVAL, "OneWire_sensor", 2048, CORE_1);
    eventy_manager.registerTask(&ACC_sensor, ACC_INTERVAL, "ACC_sensor", 2048, CORE_1);
    eventy_manager.registerTask(&GPS_sensor, GPS_INTERVAL, "GPS_sensor", 2048, CORE_1);

    eventy_manager.registerTask(&lora, LORA_INTERVAL, "LoRaTransmitter", 2048, CORE_0);
    eventy_manager.registerTask(&buzzer, BUZZER_INTERVAL, "Buzzer", 2048, CORE_1);
    eventy_manager.registerTask(&status_indicator, STATUS_INDICATOR_INTERVAL, "StatusIndicator", 2048, CORE_1);

    // Boot message
    eventy_manager.getEventTXHandler()->send(eventy::EventFactory::create("data/boot", time(NULL)));
    vTaskDelete(NULL);
}

void loop() {

}
