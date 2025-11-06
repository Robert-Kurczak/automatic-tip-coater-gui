#include "ZAxisConfiguratorService.hpp"

namespace ATC {
void ZAxisConfiguratorService::saveConfigToPersistentMemory() {
    persistentStorageController_.saveZAxisConfig(
        bufferedPersistentConfig_
    );
}
}