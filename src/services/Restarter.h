#ifndef RESTARTER_H
#define RESTARTER_H

#include "eventy/Event.h"
#include "eventy/Task.h"

using namespace eventy;

namespace aurora {

class Restarter : public Task {
public:
    EventCollection run() override;
    bool isReady() override;
};

}

#endif // RESTARTER_H
