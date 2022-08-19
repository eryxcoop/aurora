#ifndef AURORA_SD_WRITER_H
#define AURORA_SD_WRITER_H

#include "FS.h"
#include "SPI.h"
#include "SD.h"

#include "eventy/EventHandler.h"
#include "value/Value.h"

using namespace eventy;

namespace aurora {

class SDWriter : public EventHandler {
public:
    EventCollection handle(const EventPtr event_ptr) override;
    void begin(int cs_pin);
    bool isReady();
private:
    String present(EventPtr event_ptr);
    bool _ready = false;
    fs::File _output_file;
    fs::File openFile(const String &filename, const char *mode);
    time_t _last_flush = 0;
    size_t _bytes_counter = 0;
};

}

#endif  // AURORA_SD_WRITER_H
