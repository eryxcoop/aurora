#include "Restarter.h"

using namespace eventy;


namespace aurora {

bool Restarter::isReady() {
    return true;
}

EventCollection Restarter::run() {
    EventCollection events;

    ESP.restart();

    return events;
}

}
