#ifndef AURORA_SERIAL_PRINTER_H
#define AURORA_SERIAL_PRINTER_H

#include "eventy/EventHandler.h"
#include "eventy/Event.h"
#include "value/Value.h"

using namespace eventy;

namespace aurora {

class SerialPrinter : public EventHandler {
public:
    EventCollection handle(EventPtr event_ptr) override;
    void begin(unsigned long baud);

private:
    String present(EventPtr event_ptr);
};

}
#endif // AURORA_SERIAL_PRINTER_H
