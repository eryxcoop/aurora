#ifndef AURORA_LORA_TRANSMITTER_H
#define AURORA_LORA_TRANSMITTER_H

#include "eventy/Task.h"
#include "eventy/EventHandler.h"
#include "eventy/EventQueue.h"
#include "consumers/SensorMetricServer.h"

#include "LoRa.h"
#include "SPI.h"

using namespace eventy;

namespace aurora {

class LoRaTransmitter : public Task {
public:
    LoRaTransmitter(SensorMetricServer *metric_server, uint csPin, uint resetPin, uint irqPin, uint sck, uint miso,
                    uint mosi, uint frequency_in_mhz);
    void begin() override;
    EventCollection run() override;
    bool isReady() override;
private:
    bool _ready = false;
    SPIClass _spi;
    static const byte _local_address = 0xAA;
    static const byte _destination_address = 0xEE;
    uint _message_count = 0;
    SensorMetricServer *_metric_server;
    uint _csPin, _resetPin, _irqPin, _sck, _miso, _mosi, _frequency_in_mhz;
};

class PacketPayload {
public:
    template<class T>
    PacketPayload &operator<<(T &data);
    ~PacketPayload();
    char operator[](int index);
    void checkout();
    int size();
private:
    class ByteArray {
    public:
        ByteArray(int size, char *ptr) : size(size), ptr(ptr) {}
        int size;
        char *ptr;
    };

    int _size = 0;
    Stack <ByteArray> _staged;
    char *_payload;
};

template<class T>
PacketPayload &PacketPayload::operator<<(T &data) {
    _size += sizeof(T);
    char *ptr = new char[sizeof(T)];
    *(T *) ptr = data;
    _staged.push(ByteArray(sizeof(T), ptr));
    return *this;
}

}

#endif  // AURORA_LORA_TRANSMITTER_H
