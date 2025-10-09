#include "YAxisConfiguratorService.hpp"

namespace ATC {
void YAxisConfiguratorService::saveConfigToPersistentMemory() {
    persistentStorageController_.saveXAxisConfig(
        bufferedPersistentConfig_
    );
}
}