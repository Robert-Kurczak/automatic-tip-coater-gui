#include "XAxisConfiguratorService.hpp"

namespace ATC {
void XAxisConfiguratorService::saveConfigToPersistentMemory() {
    // TODO remove separate buffered fields in favor of the whole buffered
    // config structure?
    const AxisPersistentConfig newConfig {
        .startPosition = bufferedStartPosition_,
        .endPosition = bufferedEndPosition_,
        .speed = bufferedSpeed_
    };

    persistentStorageController_.saveXAxisConfig(newConfig);
}
}
