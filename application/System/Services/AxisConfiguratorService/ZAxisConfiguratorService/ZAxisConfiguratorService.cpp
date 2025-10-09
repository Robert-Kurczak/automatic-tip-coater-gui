#include "ZAxisConfiguratorService.hpp"

namespace ATC {
void ZAxisConfiguratorService::saveConfigToPersistentMemory() {
    persistentStorageController_.saveXAxisConfig(
        bufferedPersistentConfig_
    );
}
}