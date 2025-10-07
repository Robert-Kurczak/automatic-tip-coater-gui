#include "ZAxisConfiguratorService.hpp"

namespace ATC {
void ZAxisConfiguratorService::saveConfigToPersistentMemory() {
    persistentStorageController_.saveXAxisConfig(bufferedConfig_);
}
}