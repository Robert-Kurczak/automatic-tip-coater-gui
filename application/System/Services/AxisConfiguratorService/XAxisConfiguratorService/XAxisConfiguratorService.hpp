#pragma once

#include "../AxisConfiguratorService.hpp"

namespace ATC {
class XAxisConfiguratorService : public AxisConfiguratorService {
protected:
    virtual void saveConfigToPersistentMemory() override;

public:
    using AxisConfiguratorService::AxisConfiguratorService;
};
}