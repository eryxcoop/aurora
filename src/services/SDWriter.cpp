#include "SDWriter.h"

using namespace eventy;

namespace aurora {

void SDWriter::begin(int cs_pin) {
    pinMode(cs_pin, OUTPUT);
    _ready = SD.begin();
    delay(50);
    _ready = SD.begin(); // evil double begin() hack... para mas placer
    delay(50);
    if ((_output_file = openFile("data_test_latest.csv", FILE_APPEND))) {
        _ready = true;
        _bytes_counter = _output_file.position();
        Serial.println("SD BEGIN!");
    }
}

bool SDWriter::isReady() {
    return _ready;
}

fs::File SDWriter::openFile(const String &filename, const char *mode) {
    return SD.open("/" + filename, mode);
}

EventCollection SDWriter::handle(EventPtr event_ptr) {
    EventCollection events;

    if (!isReady()) {
        return events;
    }

    _bytes_counter += _output_file.println(present(event_ptr));

    time_t now = time(NULL) / 20;
    if (_last_flush < now) {
        _output_file.flush();
        _last_flush = now;

        if (_output_file.position() != _bytes_counter) {
            events.push(EventFactory::create("info/sd/error", _bytes_counter - _output_file.position()));
            _bytes_counter = _output_file.position();
        } else {
            events.push(EventFactory::create("info/sd/ok"));
        }
    }

    return events;
}

String SDWriter::present(EventPtr event_ptr) {
    String out = String(time(NULL)) + "," + String(event_ptr->topic());
    switch (event_ptr->type()) {
        case EVENT_TYPE_BOOL: {
            out = out + "," + String(((Event<bool> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_INT: {
            out = out + "," + String(((Event<int> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_UINT: {
            out = out + "," + String(((Event<unsigned int> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_LONG: {
            out = out + "," + String(((Event<long> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_ULONG: {
            out = out + "," + String(((Event<unsigned long> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_FLOAT: {
            out = out + "," + String(((Event<float> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_DOUBLE: {
            out = out + "," + String(((Event<double> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_GPS: {
            PositionalData data = ((Event <PositionalData> *) event_ptr)->value();
            out = out + "," + String(data.altitude()) + ":" + String(data.longitude()) + ":" + String(data.hour()) +
                  ":" + String(data.minute()) + ":" + String(data.second());
            break;
        }
        default: {
            out = out + ", UNK";
        }
    }
    return out;
}

}
