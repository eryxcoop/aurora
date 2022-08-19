#include "SerialPrinter.h"

using namespace eventy;

namespace aurora {

void SerialPrinter::begin(unsigned long baud) {
    Serial.begin(baud);
}

EventCollection SerialPrinter::handle(EventPtr event_ptr) {
    Serial.println(present(event_ptr));
    return {};
};

String SerialPrinter::present(EventPtr event_ptr) {
    String out = "";
    out = out + "Topic: " + String(event_ptr->topic()) + ", ";
    switch (event_ptr->type()) {
        case EVENT_TYPE_BOOL: {
            out = out + "Value: " + String(((Event<bool> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_INT: {
            out = out + "Value:" + String(((Event<int> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_UINT: {
            out = out + "Value:" + String(((Event<unsigned int> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_LONG: {
            out = out + "Value:" + String(((Event<long> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_ULONG: {
            out = out + "Value:" + String(((Event<unsigned long> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_FLOAT: {
            out = out + "Value:" + String(((Event<float> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_DOUBLE: {
            out = out + "Value:" + String(((Event<double> *) event_ptr)->value());
            break;
        }
        case EVENT_TYPE_GPS: {
            PositionalData data = ((Event <PositionalData> *) event_ptr)->value();
            out = out + "Value: " + String(data.altitude()) + ":" + String(data.longitude()) + ":" +
                  String(data.hour()) + ":" + String(data.minute()) + ":" + String(data.second());
            break;
        }
        default: {
            out = out + "Value: UNK";
        }
    }
    return out;
}

}
