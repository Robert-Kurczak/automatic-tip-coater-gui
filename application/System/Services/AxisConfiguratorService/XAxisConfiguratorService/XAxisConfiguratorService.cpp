#include "XAxisConfiguratorService.hpp"

namespace ATC {
void XAxisConfiguratorService::saveConfigToPersistentMemory() {
    getPersistentStorageController().saveXAxisConfig(
        getBufferedPersistentConfig()
    );
}
}
