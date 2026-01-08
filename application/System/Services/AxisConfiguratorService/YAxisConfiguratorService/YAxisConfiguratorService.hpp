#pragma once

#include "../AxisConfiguratorService.hpp"

namespace ATC {
class YAxisConfiguratorService : public AxisConfiguratorService {
protected:
    void saveConfigToPersistentMemory() override;

public:
    using AxisConfiguratorService::AxisConfiguratorService;
};
}