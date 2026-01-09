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
    SystemRoot(const SystemRoot&) = delete;
    SystemRoot& operator=(const SystemRoot&) = delete;
    SystemRoot(SystemRoot&&) = delete;
    SystemRoot& operator=(SystemRoot&&) = delete;
    ~SystemRoot() = default;

    void init();
    void tick();

    SystemApi& getSystemApi();
};
}