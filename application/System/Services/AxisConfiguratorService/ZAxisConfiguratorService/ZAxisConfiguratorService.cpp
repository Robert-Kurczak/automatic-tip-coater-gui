#include "ZAxisConfiguratorService.hpp"

namespace ATC {
void ZAxisConfiguratorService::saveConfigToPersistentMemory() {
    getPersistentStorageController().saveZAxisConfig(
        getBufferedPersistentConfig()
    );
}
}