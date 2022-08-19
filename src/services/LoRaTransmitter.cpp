#include "LoRaTransmitter.h"

using namespace eventy;

namespace aurora {

void PacketPayload::checkout() {
    int position = _size;
    _payload = new char[_size];
    while (!_staged.isEmpty()) {
        ByteArray byte_array = _staged.pop();
        position -= byte_array.size;
        memmove(_payload + position, byte_array.ptr, byte_array.size);
        delete[] byte_array.ptr;
    }
}

PacketPayload::~PacketPayload() {
    if (_payload != nullptr)
        delete[] _payload;
}

int PacketPayload::size() {
    return _size;
}

char PacketPayload::operator[](int index) {
    return _payload[index];
}

LoRaTransmitter::LoRaTransmitter(SensorMetricServer *metric_server, uint csPin, uint resetPin, uint irqPin, uint sck,
                                 uint miso, uint mosi, uint frequency_in_mhz) :
        _metric_server(metric_server),
        _csPin(csPin),
        _resetPin(resetPin),
        _irqPin(irqPin),
        _sck(sck),
        _miso(miso),
        _mosi(mosi),
        _frequency_in_mhz(frequency_in_mhz) {
}

// TODO: modificar para que sea seguro de llamar multiples veces
void LoRaTransmitter::begin() {
    _spi.begin(_sck, _miso, _mosi, _csPin);
    LoRa.setSPI(_spi);
    LoRa.setPins(_csPin, _resetPin, _irqPin);
    if (!LoRa.begin(_frequency_in_mhz * 1E6)) {
        Serial.println("LoRa init failed. Check your connections.");
        _ready = false;
    } else {
        Serial.println("AuroraLoRa begin!");
        LoRa.setCodingRate4(8);
        LoRa.enableCrc();
        LoRa.setSpreadingFactor(12);
        LoRa.setTxPower(20);
        // LoRa.setSignalBandwidth(125E3);
        _ready = true;
    }
}

bool LoRaTransmitter::isReady() {
    return _ready;
}

EventCollection LoRaTransmitter::run() {
    EventCollection events;

    PositionalData positional_data = _metric_server->positionalData();
    double inner_temperature = _metric_server->innerTemperature();
    double outer_temperature = _metric_server->outerTemperature();

    u_int8_t hours = positional_data.hour();
    u_int8_t minutes = positional_data.minute();
    u_int8_t seconds = positional_data.second();
    int latitude_int = positional_data.latitude() * 1E6;
    int longitude_int = positional_data.longitude() * 1E6;
    int altitude_int = positional_data.altitude();
    short inner_temperature_short = inner_temperature * 1E2;
    short outer_temperature_short = outer_temperature * 1E2;
    int altitude_bmp = _metric_server->altitude();

    PacketPayload packet_payload;
    packet_payload << hours << minutes << seconds << latitude_int << longitude_int << altitude_int;
    packet_payload << inner_temperature_short << outer_temperature_short;
    packet_payload << altitude_bmp;
    packet_payload.checkout();

    LoRa.beginPacket();
    LoRa.write(_destination_address);
    LoRa.write(_local_address);
    LoRa.write(_message_count);
    LoRa.write(packet_payload.size());
    for (int i = 0; i < packet_payload.size(); i++)
        LoRa.print(packet_payload[i]);
    LoRa.endPacket();
    _message_count++;

    events.push(EventFactory::create("info/lora/ok", packet_payload.size()));

    return events;
}

}
