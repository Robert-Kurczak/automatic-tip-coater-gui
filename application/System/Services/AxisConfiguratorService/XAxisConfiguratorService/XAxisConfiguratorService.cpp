#include "XAxisConfiguratorService.hpp"

namespace ATC {
void XAxisConfiguratorService::saveConfigToPersistentMemory() {
    persistentStorageController_.saveXAxisConfig(bufferedConfig_);
}
}
