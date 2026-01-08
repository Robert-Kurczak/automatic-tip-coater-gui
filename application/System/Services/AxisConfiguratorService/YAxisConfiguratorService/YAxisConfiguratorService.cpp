#include "YAxisConfiguratorService.hpp"

namespace ATC {
void YAxisConfiguratorService::saveConfigToPersistentMemory() {
    getPersistentStorageController().saveYAxisConfig(
        getBufferedPersistentConfig()
    );
}
}