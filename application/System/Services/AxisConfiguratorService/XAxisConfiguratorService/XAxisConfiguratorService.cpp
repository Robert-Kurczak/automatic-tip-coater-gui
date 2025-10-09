#include "XAxisConfiguratorService.hpp"

namespace ATC {
void XAxisConfiguratorService::saveConfigToPersistentMemory() {
    persistentStorageController_.saveXAxisConfig(
        bufferedPersistentConfig_
    );
}
}
