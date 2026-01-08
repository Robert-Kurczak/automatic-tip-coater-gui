#pragma once

#include "../AxisConfiguratorService.hpp"

namespace ATC {
class ZAxisConfiguratorService : public AxisConfiguratorService {
protected:
    void saveConfigToPersistentMemory() override;

public:
    using AxisConfiguratorService::AxisConfiguratorService;
};
}