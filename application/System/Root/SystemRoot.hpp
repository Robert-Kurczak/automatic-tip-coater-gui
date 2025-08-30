#pragma once

#include "SystemApi.hpp"
#include "SystemComponents.hpp"

namespace ATC {
class SystemRoot {
private:
    SystemComponents& systemComponents_;
    SystemApi& systemApi_;

public:
    SystemRoot(SystemComponents& systemComponents, SystemApi& systemApi);

    void init();
    void tick();

    SystemApi& getSystemApi();
};
}