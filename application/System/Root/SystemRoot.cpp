#include "SystemRoot.hpp"

namespace ATC {
SystemRoot::SystemRoot(
    SystemComponents& systemComponents,
    SystemApi& systemApi
) :
    systemComponents_(systemComponents),
    systemApi_(systemApi) {}

void SystemRoot::init() {
    systemComponents_.xAxisController.init();
    systemComponents_.yAxisController.init();
    systemComponents_.zAxisController.init();
    systemComponents_.spindleController.init();
    systemComponents_.heaterController.init();
    systemComponents_.display.init();
    systemComponents_.touchPanelController.init();
}

void SystemRoot::tick() {
    systemComponents_.xAxisController.tick();
    systemComponents_.yAxisController.tick();
    systemComponents_.zAxisController.tick();
    systemComponents_.spindleController.tick();
    systemComponents_.heaterController.tick();
    systemComponents_.taskScheduler.tick();
}

SystemApi& SystemRoot::getSystemApi() {
    return systemApi_;
}
}