#include "YAxisConfiguratorService.hpp"

namespace ATC {
void YAxisConfiguratorService::saveConfigToPersistentMemory() {
    persistentStorageController_.saveYAxisConfig(
        bufferedPersistentConfig_
    );
}
}