#pragma once

#include "../AxisConfiguratorService.hpp"

namespace ATC {
class XAxisConfiguratorService : public AxisConfiguratorService {
protected:
    void saveConfigToPersistentMemory() override;

public:
    using AxisConfiguratorService::AxisConfiguratorService;
};
}