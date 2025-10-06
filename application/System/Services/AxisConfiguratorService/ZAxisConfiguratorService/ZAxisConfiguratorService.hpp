#pragma once

#include "../AxisConfiguratorService.hpp"
#include "application/System/Controllers/PersistentStorageController/IPersistentStorageController.hpp"

namespace ATC {
class ZAxisConfiguratorService : public AxisConfiguratorService {
protected:
    virtual void saveConfigToPersistentMemory() override;

public:
    using AxisConfiguratorService::AxisConfiguratorService;
};
}